#include "WSocket.h"
#include "log.h"

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
