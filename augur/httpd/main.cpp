#include <cstdio>
#include "Server.h"
#include <iostream>
#include "Config.h"
#include "FastCGI.h"
#include "MD5.h"

int main()
{
    //Server server;
    //server.dispatch();
    /*std::shared_ptr<WSocket> socket = std::make_shared<WSocket>(SOCKET_TYPE::INET);
    socket->connect("127.0.0.1", 9000);
    std::map<std::string, std::string> params = {
        {"SCRIPT_FILENAME", "/home/wyc/code/html/index.php"},
        {"REQUEST_METHOD", "GET"}
    };
    FCGI::write(socket->native(), 1, params);
    FCGI::read(socket->native());*/
    MD5 m;
    return 0;
}