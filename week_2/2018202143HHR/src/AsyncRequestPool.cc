#include <sys/wait.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <fcntl.h>
#include <cassert>
#include <cstring>

#include "AsyncRequestPool.h"

static void checkErrno(const char *message) {
    if (errno) {
        perror(message);
        abort();
    }
}

static void setNonBlock(int fd) {
    assert(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) == 0);
}

static void epollCtl(int epoll_fd, int op, int fd) {
    epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    if (epoll_ctl(epoll_fd, op, fd, &ev) != 0) checkErrno("epoll_ctl");
}

static bool tryRead(int fd, void *buffer, size_t buffer_size, size_t &read_size) {
    ssize_t res = read(fd, buffer, buffer_size);
    if (res < 0) {
        if (errno == EAGAIN) return false; // Data is not ready
        checkErrno("tryRead");
    } else {
        read_size = res;
        return true;
    }

    return false;
}

static void processWgetError(std::string &message) {
    message.erase(message.find_last_not_of("\n\t ") + 1);

    size_t lastNewline = message.find_last_of("\n");
    if (lastNewline != std::string::npos) {
        message = message.substr(lastNewline + 1);
    }
}

void AsyncRequestPool::startWget(Request &request) {
    int pipeOutput[2];
    if (pipe(pipeOutput) != 0) checkErrno("pipe");

    int pipeError[2];
    if (pipe(pipeError) != 0) checkErrno("pipe");

    const char *url = request.url.c_str();

    int fork_result = vfork();
    if (fork_result < 0) {
        checkErrno("vfork");
    }
    if (fork_result > 0) {
        // Parent
        request.fdOutput = pipeOutput[0];
        request.fdError = pipeError[0];
        request.fdOutputWrite = pipeOutput[1];
        request.fdErrorWrite = pipeError[1];

        setNonBlock(request.fdOutput);
        setNonBlock(request.fdError);

        epollCtl(epoll_fd, EPOLL_CTL_ADD, request.fdOutput);
        epollCtl(epoll_fd, EPOLL_CTL_ADD, request.fdError);

        request.wgetPID = fork_result;

        request.responseBody.reserve(STRING_RESERVE_SPACE);
        request.standardError.reserve(STRING_RESERVE_SPACE);
    } else {
        // Child
        dup2(pipeOutput[1], STDOUT_FILENO);
        dup2(pipeError[1], STDERR_FILENO);
        execlp(WGET_COMMAND,
               WGET_COMMAND,
               "-O-",
               "-o/dev/stderr",
               "-4",
               "--timeout=" WGET_TIMEOUT,
               "--waitretry=" WGET_WAITRETRY,
               "--tries=" WGET_TRIES,
               url,
               NULL);

        // execlp fails
        perror("execlp");
        exit(10); // wget's return code is in [0, 8] -- from man wget(1)
    }
}

void AsyncRequestPool::addTask(const std::string &url, std::function<void(std::string &, std::string &)> &&callback) {
    Request request;
    request.url = url;
    request.callback = callback;

    if (runningRequests.size() == MAX_CONCURRENTE_COUNT) {
        requestQueue.push(request);
    } else {
        startWget(request);
        runningRequests.push_back(std::move(request));
    }
}

AsyncRequestPool::AsyncRequestPool() {
    // Create epoll
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) checkErrno("epoll_create1");

    // Create a signalfd
    sigset_t sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    signal_fd = signalfd(-1, &sigmask, SFD_NONBLOCK);

    epollCtl(epoll_fd, EPOLL_CTL_ADD, signal_fd);
}

AsyncRequestPool::~AsyncRequestPool() {
    epollCtl(epoll_fd, EPOLL_CTL_DEL, signal_fd);

    close(signal_fd);
    close(epoll_fd);
}

void AsyncRequestPool::runEventLoop() {
    while (!runningRequests.empty()) {
        signalfd_siginfo si;
        while (read(signal_fd, &si, sizeof(si)) == sizeof(si));

        std::list<Request> newRunningRequests;
        for (auto &request : runningRequests) {
            bool running = true;
            // Check if the wget's process running before read from pipe to
            // avoid closing the pipe after it exit but before read some data.
            // Non-blocking waitpid() returns 0 if no process exited.
            int return_code;
            if (waitpid(request.wgetPID, &return_code, WNOHANG)) {
                running = false;
            }

            char buffer[READ_BUFFER_SIZE];
            size_t read_size;

            while (tryRead(request.fdOutput, buffer, READ_BUFFER_SIZE, read_size)) {
                request.responseBody.append(buffer, read_size);
            }

            while (tryRead(request.fdError, buffer, READ_BUFFER_SIZE, read_size)) {
                request.standardError.append(buffer, read_size);
            }

            if (!running) {
                epollCtl(epoll_fd, EPOLL_CTL_DEL, request.fdOutput);
                epollCtl(epoll_fd, EPOLL_CTL_DEL, request.fdError);

                close(request.fdOutput);
                close(request.fdError);
                close(request.fdOutputWrite);
                close(request.fdErrorWrite);
                if (return_code) {
                    processWgetError(request.standardError);
                } else {
                    request.standardError = "";
                }
                request.callback(request.standardError, request.responseBody);

                if (!requestQueue.empty()) {
                    Request request = std::move(requestQueue.front());
                    requestQueue.pop();

                    startWget(request);

                    newRunningRequests.push_back(std::move(request));
                }
            } else newRunningRequests.push_back(std::move(request));
        }

        runningRequests = std::move(newRunningRequests);

        if (!runningRequests.empty()) {
            epoll_event events[1];
            epoll_wait(epoll_fd, events, 1, -1);
        }
    }
}
