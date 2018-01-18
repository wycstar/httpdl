#pragma once
#include <sys/epoll.h>
#include <unistd.h>
#include <memory>

class WPoll
{
private:
    int _fd;
    std::shared_ptr<struct epoll_event> _events;
    static const int MAX_EVENTS = 32768;

public:
    WPoll();
    ~WPoll();
    void add(int fd, bool is_oneshort = true);
    void reset_oneshot(int fd);
    int wait();
    struct epoll_event* events();
    int native();
};

