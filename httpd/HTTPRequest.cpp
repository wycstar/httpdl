#include "HTTPRequest.h"

HTTPRequest::HTTPRequest()
{
}

HTTPRequest::HTTPRequest(const char * request):
    _header(request),
    _error_code(HTTPUtil::HTTP_OK),
    _accept("*/*")
{
    _parse();
}

HTTPRequest::~HTTPRequest()
{
}

void HTTPRequest::_parse()
{
    std::string::size_type start = 0;
    std::vector<std::string> request_line = HTTPUtil::split(_header, "\r\n");
    if (request_line.size() == 0) {
        return;
    }
    if (request_line[0].substr(start, 3) == "GET") {
        _method = HTTPUtil::GET;
        start = 4;
    }
    else if (request_line[0].substr(start, 4) == "POST") {
        _method = HTTPUtil::POST;
        start = 5;
    }
    else if (request_line[0].substr(start, 3) == "PUT") {
        _method = HTTPUtil::PUT;
        start = 4;
    }
    else if (request_line[0].substr(start, 6) == "DELETE") {
        _method = HTTPUtil::DELETE;
        start = 7;
    }
    else {
        _method = HTTPUtil::UNIMPLEMENTED;
        return;
    }
    _uri = request_line[0].substr(start, request_line[0].find_last_of(" ") - start);
    start = request_line[0].find_last_of("/");
    _version = request_line[0].substr(start + 1, request_line[0].find_first_of("\r") - start);
    for (size_t index = 1; index < request_line.size() - 1; index++) {
        auto sep = request_line[index].find_first_of(":");
        _line_map.insert(std::pair <std::string, std::string>(
            request_line[index].substr(0, sep),
            request_line[index].substr(sep + 2, request_line[index].length())
        ));
    }
    auto accept = _line_map.find("Accept");
    if (accept != _line_map.end()) {
        auto a = HTTPUtil::parse_mime(accept->second);
        _accept = a[0].first;
    }
}

HTTPUtil::HTTP_METHOD HTTPRequest::get_method()
{
    return _method;
}

std::string HTTPRequest::get_version()
{
    return _version;
}

std::string HTTPRequest::get_uri()
{
    return _uri;
}

HTTPUtil::HTTP_STATUS_CODE HTTPRequest::get_error()
{
    return _error_code;
}

HTTPUtil::HTTP_UA HTTPRequest::get_ua()
{
    return HTTPUtil::HTTP_UA();
}

std::string HTTPRequest::get_mime()
{
    return _accept;
}
