#pragma once
#include "WSocket.h"
#include <memory>
#include <map>
#pragma pack(1)

namespace FCGI {
    typedef enum:unsigned char {
        BEGIN_REQUEST = 1,
        ABORT_REQUEST = 2,
        END_REQUEST = 3,
        SET_ENV = 4,
        STDIN = 5,
        STDOUT = 6,
        STDERR = 7
    }FCGI_HEADER_TYPE;

    typedef struct _tFCGI_HEADER {
        unsigned char version;
        FCGI_HEADER_TYPE type;
        unsigned char id[2];
        unsigned char length[2];
        unsigned char padding;
        unsigned char reversed;
    }FCGI_HEADER;

    typedef struct _tFCGI_START_BODY {
        unsigned char role[2];
        unsigned char is_keep;
        unsigned char reversed[5];
    }FCGI_START_BODY;

    typedef struct _tFCGI_END_BODY {
        unsigned char app_status[4];
        unsigned char protocol_status;
        unsigned char reversed[3];
    }FCGI_END_BODY;

    typedef struct _tFCGI_REQUEST {
        FCGI_HEADER header;
        FCGI_START_BODY body;
    }FCGI_REQUEST;

    typedef struct _tFCGI_RESPONSE {
        FCGI_HEADER header;
        FCGI_END_BODY body;
    }FCGI_RESPONSE;

    typedef enum:unsigned short {
        RESPONDER = 1,
        AUTHORIZER = 2,
        FILTER = 3
    }FCGI_BODY_ROLE;

    void begin_request(const int& fd, const unsigned short& id);
    void end_request(const int& fd, const unsigned short& id);
    FCGI_HEADER make_header(const unsigned short& id, FCGI_HEADER_TYPE type = FCGI_HEADER_TYPE::BEGIN_REQUEST, unsigned short length = 8, unsigned char padding = 0);
    FCGI_START_BODY make_request_body(FCGI_BODY_ROLE role = FCGI_BODY_ROLE::RESPONDER, bool is_keep = false);
    void set_env(const int& fd, unsigned short id, std::string key, std::string value);
    void write(const int & fd, const unsigned short &id, const std::map<std::string, std::string>& params);
    void read(const int& fd);
}
