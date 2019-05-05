#ifndef _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H
#define _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H

#include <sys/types.h>
#include <unistd.h>

#include <memory>
#include <list>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include "StringEx.h"
#include "Url.h"
#include "RequestOptions.h"

struct Request {
    int fdStdout, fdStderr;
    int fdStdoutWrite, fdStderrWrite;
    pid_t wgetPID;

    Url url;
    StringEx dataStdout, dataStderr;
    std::function<void (bool, const StringEx &, const StringEx &, const Url &)> callback;

    struct ReadEvent {
        int &fd;
        StringEx &dataStorage;
    } eventStdout, eventStderr;

    Request() : eventStdout({fdStdout, dataStdout}), eventStderr({fdStderr, dataStderr}) {}
};

class AsyncRequestPool {
    // The current running requests.
    std::list<std::shared_ptr<Request>> runningRequests;

    // The pending request to run, due to limit of --max-concurrent-count.
    std::queue<std::shared_ptr<Request>> requestQueue;

    // File descriptor for epoll and signalfd (to get notified when a child (wget) process) exits.
    int fdEpoll, fdSignalfd;

    // Options from command-line arguments.
    RequestOptions requestOptions;

    // The map from a wget process's pid to its Request.
    // Used when a SIGCHLD (child process exit) is notified by epolling signalfd to
    // query the associated request object.
    std::unordered_map<pid_t, std::list<std::shared_ptr<Request>>::iterator> mapPidRequest;

    // A set of all current running request's ReadEvent.
    // Used to check if a epoll event's returning pointer of ReadEvent is valid.
    // Sometimes epoll_wait returns signalfd's SIGCHLD signal first and then return
    // the associated pipe's available-to-read event. So after a Request object is
    // destroied, a following available-to-read event of that request may be fired
    // and cause the program attempts to got fd and dataStorage from a already destroied
    // ReadEvent object.
    std::unordered_set<Request::ReadEvent *> setValidReadEvent;

    pid_t startWget(std::shared_ptr<Request> request);
    void startTask(std::shared_ptr<Request> request);

public:
    AsyncRequestPool(const RequestOptions &requestOptions);
    ~AsyncRequestPool();
    void addTask(const Url &url, std::function<void (bool, const StringEx &, const StringEx &, const Url &)> &&callback);
    void runEventLoop();
};

#endif // _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H
