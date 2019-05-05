#include <sys/wait.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <fcntl.h>
#include <cassert>
#include <cstring>
#include <regex>
#include <tuple>

#include "AsyncRequestPool.h"

constexpr size_t STRING_RESERVE_SPACE  = (256 * 1024);   // 256 KiB
constexpr size_t READ_BUFFER_SIZE      = (32 * 1024);    // 32 KiB
constexpr int    WGET_EXIT_EXEC_FAILED = 9;              // Wget's return code is in [0, 8] -- from man wget(1).

static void checkError(const char *message) {
    if (errno) {
        perror(message);
        abort();
    }
}

static void setNonBlock(int fd) {
    assert(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) == 0);
}

static void setEpoll(int fdEpoll, int op, int fd, void *data) {
    epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.ptr = data;
    if (epoll_ctl(fdEpoll, op, fd, &ev) != 0) checkError("epoll_ctl");
}

static bool tryRead(int fd, void *buffer, size_t buffer_size, size_t &readSize) {
    ssize_t res = read(fd, buffer, buffer_size);
    if (res < 0) {
        if (errno == EAGAIN) return false; // Data is not ready.
        checkError("read");
    } else {
        readSize = res;
        return true;
    }

    return false;
}

static std::tuple<StringEx, Url> parseWgetOutput(std::shared_ptr<Request> request, int returnCode) {
    // Extract redirected url.
    static const std::regex reRedirectUrl("Location: (.+) \\[following\\]");
    Url redirectedUrl = request->url;
    for (std::sregex_iterator it(request->dataStderr.begin(), request->dataStderr.end(), reRedirectUrl);
         it != std::sregex_iterator();
         it++) {
        auto &match = *it;
        redirectedUrl = Url((StringEx)match[1], redirectedUrl);
    }

    StringEx errorMessage;
    if (returnCode != 0) {
        // Extract error message.
        errorMessage = request->dataStderr;

        errorMessage.erase(errorMessage.findLastNotOf("\n\t ") + 1);
        size_t lastNewline = errorMessage.findLastOf("\n");
        if (lastNewline != StringEx::npos) {
            errorMessage = errorMessage.substr(lastNewline + 1);
        }
    }

    return std::make_tuple(errorMessage, redirectedUrl);
}

pid_t AsyncRequestPool::startWget(std::shared_ptr<Request> request) {
    int pipeOutput[2];
    if (pipe(pipeOutput) != 0) checkError("pipe");

    int pipeError[2];
    if (pipe(pipeError) != 0) checkError("pipe");

    StringEx &&string_url = request->url.toString();
    const char *url = string_url.getData();

    // For wget command line arguments.
    StringEx argTimeout = "--timeout=" + std::to_string(requestOptions.wgetTimeout);
    StringEx argWaitRetry = "--waitretry=" + std::to_string(requestOptions.wgetWaitRetry);
    StringEx argTries = "--tries=" + std::to_string(requestOptions.wgetTries);

    pid_t pid = vfork();
    if (pid < 0) {
        checkError("vfork");
    }
    if (pid > 0) {
        // Parent.
        request->fdStdout = pipeOutput[0];
        request->fdStderr = pipeError[0];
        request->fdStdoutWrite = pipeOutput[1];
        request->fdStderrWrite = pipeError[1];

        setNonBlock(request->fdStdout);
        setNonBlock(request->fdStderr);

        setEpoll(fdEpoll, EPOLL_CTL_ADD, request->fdStdout, &request->eventStdout);
        setEpoll(fdEpoll, EPOLL_CTL_ADD, request->fdStderr, &request->eventStderr);

        request->wgetPID = pid;

        request->dataStdout.reserve(STRING_RESERVE_SPACE);
        request->dataStderr.reserve(STRING_RESERVE_SPACE);

        return pid;
    } else {
        // Child.
        dup2(pipeOutput[1], STDOUT_FILENO);
        dup2(pipeError[1], STDERR_FILENO);
        execlp(requestOptions.wgetCommand.getData(),
               requestOptions.wgetCommand.getData(),
               "-O-",
               "-o/dev/stderr",
               "-4",
               argTimeout.getData(),
               argWaitRetry.getData(),
               argTries.getData(),
               url,
               NULL);

        // Execlp failed.
        exit(WGET_EXIT_EXEC_FAILED);
    }
}

void AsyncRequestPool::startTask(std::shared_ptr<Request> request) {
    pid_t pid = startWget(request);

    setValidReadEvent.insert(&request->eventStdout);
    setValidReadEvent.insert(&request->eventStderr);

    runningRequests.push_back(request);
    mapPidRequest[pid] = --runningRequests.end();
}

void AsyncRequestPool::addTask(const Url &url, std::function<void (bool, const StringEx &, const StringEx &, const Url &)> &&callback) {
    std::shared_ptr<Request> request = std::make_shared<Request>();
    request->url = url;
    request->callback = callback;

    if (runningRequests.size() == requestOptions.maxConcurrenteCount) {
        requestQueue.push(request);
    } else {
        startTask(request);
    }
}

AsyncRequestPool::AsyncRequestPool(const RequestOptions &requestOptions) : requestOptions(requestOptions) {
    // Create epoll.
    fdEpoll = epoll_create1(0);
    if (fdEpoll == -1) checkError("epoll_create1");

    // Create a signalfd.
    sigset_t sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    fdSignalfd = signalfd(-1, &sigmask, SFD_NONBLOCK);

    setEpoll(fdEpoll, EPOLL_CTL_ADD, fdSignalfd, NULL);
}

AsyncRequestPool::~AsyncRequestPool() {
    setEpoll(fdEpoll, EPOLL_CTL_DEL, fdSignalfd, NULL);

    close(fdSignalfd);
    close(fdEpoll);
}

void AsyncRequestPool::runEventLoop() {
    while (!runningRequests.empty()) {
        epoll_event event;
        epoll_wait(fdEpoll, &event, 1, -1);

        // A epoll event is either a child (wget) process exited, or a pipe is
        // available to read. The former's epoll_data is empty while the later's
        // contains a pointer to a Request object's eventStdout or eventStderr.
        // That is how we idenfity epoll events.

        if (event.data.ptr) {
            // A pipe is available to read.
            Request::ReadEvent *e = static_cast<Request::ReadEvent *>(event.data.ptr);

            if (setValidReadEvent.count(e) == 0) {
                // The ReadEvent's associated Request is already destroied.
                // Because epoll returns signalfd's SIGCHLD before returning this 
                // available-to-read event (of the pipe of the already-exited process).
                continue;
            }

            char buffer[READ_BUFFER_SIZE];
            size_t readSize;

            while (tryRead(e->fd, buffer, READ_BUFFER_SIZE, readSize)) {
                e->dataStorage.append(buffer, readSize);
            }
        } else {
            // One or more child (wget) processes exited.
            signalfd_siginfo si;
            assert(read(fdSignalfd, &si, sizeof(si)) == sizeof(si));

            // According to man signal(7), multiple SIGCHLD may be merged into one to
            // send to our process, so check for as many exited processes as possible.
            // Call waitpid to get each exited pid and its return code.
            int status;
            pid_t pid;
            while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
                // Get associated Request object.
                std::unordered_map<pid_t, std::list<std::shared_ptr<Request>>::iterator>::iterator itMap = mapPidRequest.find(pid);
                assert(itMap != mapPidRequest.end());

                std::list<std::shared_ptr<Request>>::iterator it = itMap->second;
                std::shared_ptr<Request> request = *it;

                // Read remaining data if any to prevent data loss.
                char buffer[READ_BUFFER_SIZE];
                size_t readSize;

                while (tryRead(request->fdStdout, buffer, READ_BUFFER_SIZE, readSize)) {
                    request->dataStdout.append(buffer, readSize);
                }

                while (tryRead(request->fdStderr, buffer, READ_BUFFER_SIZE, readSize)) {
                    request->dataStderr.append(buffer, readSize);
                }

                // Finalization.
                setEpoll(fdEpoll, EPOLL_CTL_DEL, request->fdStdout, &request->eventStdout);
                setEpoll(fdEpoll, EPOLL_CTL_DEL, request->fdStderr, &request->eventStderr);

                close(request->fdStdout);
                close(request->fdStderr);
                close(request->fdStdoutWrite);
                close(request->fdStderrWrite);

                const int returnCode = WEXITSTATUS(status);

                StringEx errorMessage;
                Url redirectedUrl;
                std::tie(errorMessage, redirectedUrl) = parseWgetOutput(request, returnCode);

                // Call callback function with data and error message.
                if (!WIFEXITED(status)) {
                    // Wget exited unexpectedly.
                    request->callback(true,
                                      "Wget exited unexpectedly with status " + std::to_string(status) + '.',
                                      request->dataStdout,
                                      redirectedUrl);
                } else if (returnCode == EXIT_SUCCESS) {
                    // No error.
                    request->callback(false,
                                      "",
                                      request->dataStdout,
                                      redirectedUrl);
                } else if (returnCode == WGET_EXIT_EXEC_FAILED) {
                    // Execlp failed.
                    request->callback(true,
                                      "Failed to start wget: execlp failed.",
                                      request->dataStdout,
                                      redirectedUrl);
                } else if (returnCode >= 1 && returnCode <= 8) {
                    // Wget error.
                    request->callback(true,
                                      errorMessage,
                                      request->dataStdout,
                                      redirectedUrl);
                }

                // Remove current request from running requests list.
                runningRequests.erase(it);

                setValidReadEvent.erase(&request->eventStdout);
                setValidReadEvent.erase(&request->eventStderr);

                // Start a new request task if any in queue.
                if (!requestQueue.empty()) {
                    std::shared_ptr<Request> request = requestQueue.front();
                    requestQueue.pop();

                    startTask(request);
                }
            }
        }
    }
}
