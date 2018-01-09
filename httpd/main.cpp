#include <cstdio>
#include "Server.h"
#include "Worker.h"
#include <iostream>

int main()
{
    Server server;
    server.dispatch();
    return 0;
}