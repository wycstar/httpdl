#include "HTTPResponse.h"
#include <sstream>

HTTPResponse::HTTPResponse():
    SERVER_STRING("Augur/1.0.0")
{
}

std::string HTTPResponse::make_response(HTTPRequest & request)
{

    return std::string();
}

HTTPResponse::~HTTPResponse()
{
}
