#include "WPoll.h"
#include "WSocket.h"
#include "Worker.h"
#include "log.h"
#include "Buffer.h"

extern Worker workers;
WPoll poll;

WPoll::WPoll():_events(make_buffer<struct epoll_event>(MAX_EVENTS))
{
    _fd = epoll_create(10000);
}

WPoll::~WPoll()
{
    close(_fd);
}

void WPoll::add(int fd)
{
    struct epoll_event _ev;
    _ev.events = EPOLLIN | EPOLLET;
    _ev.data.fd = fd;
    WSocket::to_none_blocking(fd);
    int ret = epoll_ctl(_fd, EPOLL_CTL_ADD, fd, &_ev);
    if (ret != 0) {
        THROW_SYSTEM_ERROR();
    }
}

int WPoll::wait()
{
    return epoll_wait(_fd, _events.get(), MAX_EVENTS, -1);
}

struct epoll_event* WPoll::events()
{
    return _events.get();
}

int WPoll::native()
{
    return _fd;
}
