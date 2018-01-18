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
    std::vector<std::string> request_container = HTTPUtil::split(_header, "\r\n");
    if (request_container.size() == 0) return;
    _parse_request_line(request_container[0]);
    _parse_request_header(request_container);
    auto accept = _line_map.find("Accept");
    if (accept != _line_map.end()) {
        auto a = HTTPUtil::parse_mime(accept->second);
        _accept = a[0].first;
    }
    //TODO
    /*
    1·遍历conf文件夹，读入所有配置
    2·charset可以默认设置为utf-8，除非conf里有说明
    3·encoding问题暂时想到这里
    4·接下来是CGI的实现
    */
}

void HTTPRequest::_parse_request_line(std::string & line)
{
    std::string::size_type start = 0;
    if (line.substr(start, 3) == "GET") {
        _method = HTTPUtil::GET;
        start = 4;
    }
    else if (line.substr(start, 4) == "POST") {
        _method = HTTPUtil::POST;
        start = 5;
    }
    else if (line.substr(start, 3) == "PUT") {
        _method = HTTPUtil::PUT;
        start = 4;
    }
    else if (line.substr(start, 6) == "DELETE") {
        _method = HTTPUtil::DELETE;
        start = 7;
    }
    else {
        _method = HTTPUtil::UNIMPLEMENTED;
        return;
    }
    std::string url = line.substr(start, line.find_last_of(" ") - start);
    auto sep = url.find("?");
    if (sep == std::string::npos) {
        _uri = url;
    }
    else {
        _uri = url.substr(0, sep);
        std::string query(url.substr(sep + 1));
        _parse_url_params(query);
    }
    start = line.find_last_of("/");
    _version = line.substr(start + 1, line.find_first_of("\r") - start);
}

void HTTPRequest::_parse_request_header(std::vector<std::string>& container)
{
    for (size_t index = 1; index < container.size() - 1; index++) {
        auto sep = container[index].find_first_of(":");
        _line_map.insert(std::pair <std::string, std::string>(
            container[index].substr(0, sep),
            container[index].substr(sep + 2, container[index].length())
            ));
    }
}

void HTTPRequest::_parse_url_params(std::string & qs)
{
    auto s = HTTPUtil::split(qs, "&");
    for (auto i : s) {
        auto a = HTTPUtil::split(i, "=");
        _query_params.insert(std::pair<std::string, std::string>(a[0], a[1]));
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
