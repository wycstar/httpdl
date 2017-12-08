#include "HTTPRequest.h"

HTTPRequest::HTTPRequest()
{
}

HTTPRequest::~HTTPRequest()
{
}

HTTP_REQUEST HTTPRequest::parse(const string & request)
{
    string test("GET /baidu HTTP/1.1\r\n\
Host: www.hao123.com\r\n\
Connection: keep-alive\r\n\
Upgrade-Insecure-Requests: 1\r\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
Referer: https://www.baidu.com/\r\n\
Accept-Encoding: gzip, deflate, sdch\r\n\
Accept-Language: zh-CN,zh;q=0.8,en;q=0.6,zh-TW;q=0.4\r\n\
Cookie: BAIDUID=850DF3C88D4A4A87DE3DEF45E6B93065:FG=1; FLASHID=850DF3C88D4A4A87DE3DEF45E6B93065:FG=1;\ HAOSTOKEN=32d1bca5e1bd214f48046b282cca755a047661fb0321c934f20c84f453e1483d; BID=D84E7265BEDBCB9BC90DC2AFF29995C1:FG=1; hword=27\r\n\
\r\n");
    HTTP_REQUEST r;
    string::size_type start = 0;
    vector<string> request_line = _split(test, "\r\n");
  
    if (request_line[0].substr(start, 3) == "GET") {
        request_method = HTTP_METHOD::GET;
        start = 4;
    }
    else if (request_line[0].substr(start, 4) == "POST") {
        request_method = HTTP_METHOD::POST;
        start = 5;
    }
    else if (request_line[0].substr(start, 3) == "PUT") {
        request_method = HTTP_METHOD::PUT;
        start = 4;
    }
    else if (request_line[0].substr(start, 6) == "PUT") {
        request_method = HTTP_METHOD::DELETE;
        start = 7;
    }
    request_uri = request_line[0].substr(start, request_line[0].find_last_of(" ") - start);
    start = request_line[0].find_last_of("/");
    request_version = request_line[0].substr(start + 1, request_line[0].find_first_of("\r") - start);
    cout << request_uri << endl;
    cout << request_version << endl;
    return r;
}

HTTP_METHOD HTTPRequest::get_method()
{
    return HTTP_METHOD();
}

string HTTPRequest::get_version()
{
    return string();
}

string HTTPRequest::get_uri()
{
    return string();
}

HTTP_UA HTTPRequest::get_ua()
{
    return HTTP_UA();
}

vector<string> HTTPRequest::_split(const string & source, const string & sign)
{
    vector<string> result;
    string::size_type p1, p2;
    p2 = source.find(sign);
    p1 = 0;
    while (string::npos != p2) {
        result.push_back(source.substr(p1, p2 - p1));
        p1 = p2 + sign.size();
        p2 = source.find(sign, p1);
    }
    if (p1 != source.size()) {
        result.push_back(source.substr(p1));
    }
    return result;
}

