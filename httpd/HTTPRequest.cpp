#include "HTTPRequest.h"

HTTPRequest::HTTPRequest()
{
}

HTTPRequest::HTTPRequest(const char * request):_header(request), _error_code(HTTP_OK)
{
    _parse();
}

HTTPRequest::~HTTPRequest()
{
}

void HTTPRequest::_parse()
{
    std::string::size_type start = 0;
    std::vector<std::string> request_line = _split(_header, "\r\n");
    if (request_line.size() == 0) {
        return;
    }
    if (request_line[0].substr(start, 3) == "GET") {
        _method = HTTP_METHOD::GET;
        start = 4;
    }
    else if (request_line[0].substr(start, 4) == "POST") {
        _method = HTTP_METHOD::POST;
        start = 5;
    }
    else if (request_line[0].substr(start, 3) == "PUT") {
        _method = HTTP_METHOD::PUT;
        start = 4;
    }
    else if (request_line[0].substr(start, 6) == "DELETE") {
        _method = HTTP_METHOD::DELETE;
        start = 7;
    }
    else {
        _method = HTTP_METHOD::UNIMPLEMENTED;
    }
    _uri = request_line[0].substr(start, request_line[0].find_last_of(" ") - start);
    start = request_line[0].find_last_of("/");
    _version = request_line[0].substr(start + 1, request_line[0].find_first_of("\r") - start);
}

inline HTTP_METHOD HTTPRequest::get_method()
{
    return _method;
}

inline std::string HTTPRequest::get_version()
{
    return _version;
}

inline std::string HTTPRequest::get_uri()
{
    return _uri;
}

inline HTTP_STATUS_CODE HTTPRequest::get_error()
{
    return _error_code;
}

HTTP_UA HTTPRequest::get_ua()
{
    return HTTP_UA();
}

std::vector<std::string> HTTPRequest::_split(const std::string & source, const std::string & sign)
{
    std::vector<std::string> result;
    std::string::size_type p1, p2;
    p2 = source.find(sign);
    p1 = 0;
    while (std::string::npos != p2) {
        result.push_back(source.substr(p1, p2 - p1));
        p1 = p2 + sign.size();
        p2 = source.find(sign, p1);
    }
    if (p1 != source.size()) {
        result.push_back(source.substr(p1));
    }
    return result;
}

