#include <cstdio>
#include "HTTPRequest.h"

int main()
{
    string t;
    HTTPRequest a;
    a.parse(t);
    printf("hello from httpd!\n");
    return 0;
}