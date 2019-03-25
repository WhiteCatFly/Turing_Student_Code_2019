#ifndef _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H
#define _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H

#include <sys/types.h>
#include <unistd.h>

#include <list>
#include <string>
#include <queue>
#include <functional>

#include "Config.h"

struct Request {
    int fdOutput, fdError;
    int fdOutputWrite, fdErrorWrite;
    pid_t wgetPID;

    std::string url;
    std::string responseBody;
    std::string standardError;
    std::function<void(std::string &, std::string &)> callback;
};

class AsyncRequestPool {
    std::list<Request> runningRequests;
    std::queue<Request> requestQueue;
    int epoll_fd, signal_fd;

    void startWget(Request &request);

public:
    AsyncRequestPool();
    ~AsyncRequestPool();
    void addTask(const std::string &url, std::function<void(std::string &, std::string &)> &&callback);
    void runEventLoop();
};

#endif // _MENCI_WEB_CRAWLER_ASYNCREQUESTPOOL_H
