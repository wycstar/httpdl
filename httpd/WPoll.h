#pragma once
#include <sys/epoll.h>
#include <unistd.h>

class WPoll
{
private:
    int _fd;
    static const int MAX_EVENTS = 32768;

public:
    WPoll();
    ~WPoll();
    void add(int fd);
    void process();
};

