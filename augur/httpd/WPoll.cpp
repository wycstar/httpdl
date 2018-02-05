#include "WPoll.h"
#include "log.h"
#include "Buffer.h"
#include "WSocket.h"

WPoll::WPoll():_events(make_buffer<struct epoll_event>(MAX_EVENTS))
{
    _fd = epoll_create(10000);
}

WPoll::~WPoll()
{
    close(_fd);
}

void WPoll::add(int fd, bool is_oneshort)
{
    struct epoll_event _ev;
    _ev.events = EPOLLIN | EPOLLET | EPOLLOUT;
    if (is_oneshort) _ev.events |= EPOLLONESHOT;
    _ev.data.fd = fd;
    WSocket::to_none_blocking(fd);
    int ret = epoll_ctl(_fd, EPOLL_CTL_ADD, fd, &_ev);
    if (ret != 0) {
        THROW_SYSTEM_ERROR();
    }
}

void WPoll::reset_oneshot(int fd)
{
    struct epoll_event _ev;
    _ev.events = EPOLLIN | EPOLLET | EPOLLOUT | EPOLLONESHOT;
    _ev.data.fd = fd;
    int ret = epoll_ctl(_fd, EPOLL_CTL_MOD, fd, &_ev);
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
