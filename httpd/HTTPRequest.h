#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

typedef enum _tHTTP_STATUS {
    HTTP_OK = 200,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_SERVER_ERROR = 500
}HTTP_STATUS_CODE;

typedef enum _tHTTP_METHOD {
    GET,
    POST,
    PUT,
    DELETE
}HTTP_METHOD;

typedef struct _tHTTP_REQUEST{
    HTTP_METHOD method;
    string host;
    string version;
}HTTP_REQUEST;

typedef struct _tHTTP_UA {
    string os;
    string render;
    string browser_name;
    string browser_core;
    string arch;
}HTTP_UA;

class HTTPRequest
{
private:
    vector<string> _split(const string& source, const string& sign);
    HTTP_METHOD request_method;
    string request_uri;
    string request_version;

public:
    HTTPRequest();
    ~HTTPRequest();
    HTTP_REQUEST parse(const string& request);
    HTTP_METHOD get_method();
    string get_version();
    string get_uri();
    HTTP_UA get_ua();
};
