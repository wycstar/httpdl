#pragma once
#include <iostream>
#include <string>
#include "HTTPRequest.h"

class HTTPResponse
{
private:
    const std::string SERVER_STRING;

public:
    HTTPResponse();
    std::string make_response(HTTPRequest &request);
    ~HTTPResponse();
};
