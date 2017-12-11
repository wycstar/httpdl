#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

typedef enum _tSOCKET_TYPE {
    UNIX,
    INET
}SOCKET_TYPE;

class WSocket
{
private:
    int _fd;
    SOCKET_TYPE _type;

public:
    WSocket();
    WSocket(SOCKET_TYPE t);
    ~WSocket();
    int bind();
};

