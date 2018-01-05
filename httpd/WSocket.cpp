#include "WSocket.h"
#include "log.h"
#include <sys/epoll.h>
#include <sys/fcntl.h>

WSocket::WSocket()
{

}

WSocket::WSocket(SOCKET_TYPE t)
{
    _fd = socket(SOCKET_TYPE::INET ? AF_INET : AF_UNIX, SOCK_STREAM, 0);
    if (_fd == -1) {
        THROW_SYSTEM_ERROR();
    }
    int one = 1;
    int ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
    if (ret == -1) {
        THROW_SYSTEM_ERROR();
    }
    _type = t;
}

WSocket::~WSocket()
{

}

void WSocket::bind(string host = "0.0.0.0", short port = 54213)
{
    _addr.sin_addr.s_addr = inet_addr(host.c_str());
    _addr.sin_port = htons(port);
    int ret = ::bind(_fd, reinterpret_cast<sockaddr *>(&_addr), sizeof(sockaddr));
    if (ret != 0) {
        THROW_SYSTEM_ERROR();
    }
}

void WSocket::listen()
{
    int ret = ::listen(_fd, 10000);
    if (ret != 0) {
        THROW_SYSTEM_ERROR();
    }
}

void WSocket::to_none_blocking()
{
    int p = 1;
    int ret = ioctl(_fd, FIONBIO, &p);
}

void WSocket::to_none_blocking(int fd)
{
    int flag = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void WSocket::read(uint8_t *buf, uint32_t len)
{
    int ret = recv(_fd, buf, len, 0);
}
