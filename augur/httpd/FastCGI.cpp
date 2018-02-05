#include "FastCGI.h"
#include "string.h"
#include <iostream>
#include "log.h"
#include <unistd.h>

FCGI::FCGI_HEADER FCGI::make_header(const unsigned short& id, FCGI_HEADER_TYPE type, unsigned short length, unsigned char padding)
{
    FCGI_HEADER header;
    memset((char *)&header, 0, 8);
    header.version = 1;
    header.id[0] = (unsigned char)((id >> 8) & 0xff);
    header.id[1] = (unsigned char)(id & 0xff);
    header.length[0] = (unsigned char)((length >> 8) & 0xff);
    header.length[1] = (unsigned char)(length & 0xff);
    header.padding = padding;
    header.type = type;
    return header;
}

FCGI::FCGI_START_BODY FCGI::make_request_body(FCGI_BODY_ROLE role, bool is_keep)
{
    FCGI_START_BODY body;
    memset((char *)&body, 0, 8);
    body.role[0] = (unsigned char)((role >> 8) & 0xff);
    body.role[1] = (unsigned char)(role & 0xff);
    body.is_keep = is_keep ? 1 : 0;
    return body;
}

void FCGI::set_env(const int& fd, unsigned short id, std::string key, std::string value)
{
    unsigned char buf[1024];
    memset(buf, 0, sizeof(buf));
    unsigned short index = 8;
    auto key_length = key.length();
    auto value_length = value.length();
    ssize_t ret = 0;
    if (key_length < 128) {
        *(buf + (index++)) = (unsigned char)key_length;
    }
    else {
        *(buf + (index++)) = (unsigned char)(((key_length >> 24) & 0xff) | 0x80);
        *(buf + (index++)) = (unsigned char)((key_length >> 16) & 0xff);
        *(buf + (index++)) = (unsigned char)((key_length >> 8) & 0xff);
        *(buf + (index++)) = (unsigned char)(key_length & 0xff);
    }
    if (value_length < 128) {
        *(buf + (index++)) = (unsigned char)value_length;
    }
    else {
        *(buf + (index++)) = (unsigned char)(((value_length >> 24) & 0xff) | 0x80);
        *(buf + (index++)) = (unsigned char)((value_length >> 16) & 0xff);
        *(buf + (index++)) = (unsigned char)((value_length >> 8) & 0xff);
        *(buf + (index++)) = (unsigned char)(value_length & 0xff);
    }
    for (size_t i = 0; i < key_length; i++) {
        *(buf + (index++)) = (unsigned char)(key.c_str()[i]);
    }
    for (size_t i = 0; i < value_length; i++) {
        *(buf + (index++)) = (unsigned char)(value.c_str()[i]);
    }
    FCGI_HEADER header;
    header = make_header(id, FCGI::SET_ENV, index - 8);
    memcpy(buf, (char *)&header, 8);
    if ((ret = send(fd, buf, index, 0)) == -1) {
        THROW_SYSTEM_ERROR();
    };
}

void FCGI::begin_request(const int& fd, const unsigned short& id)
{
    FCGI_REQUEST request;
    ssize_t ret = 0;
    request.header = make_header(id, FCGI::BEGIN_REQUEST, 8, 0);
    request.body = make_request_body(FCGI::RESPONDER, false);
    if ((ret = send(fd, (char *)&request, sizeof(request), 0)) == -1) {
        THROW_SYSTEM_ERROR();
    };
}

void FCGI::end_request(const int & fd, const unsigned short & id)
{
    ssize_t ret = 0;
    FCGI::FCGI_HEADER header = make_header(id, FCGI::SET_ENV, 0, 0);
    if ((ret = send(fd, (char *)&header, sizeof(header), 0)) == -1) {
        THROW_SYSTEM_ERROR();
    };
}

void FCGI::write(const int & fd, const unsigned short &id, const std::map<std::string, std::string>& params)
{
    begin_request(fd, id);
    for (auto i : params) {
        set_env(fd, id, i.first, i.second);
    }
    end_request(fd, id);
}

void FCGI::read(const int & fd)
{
    FCGI_HEADER header;
    ssize_t read;
    char buf[4096];
    memset(&header, 0, sizeof(header));
    char padding[8];
    if ((read = recv(fd, (char *)&header, 8, 0)) == -1) {
        THROW_SYSTEM_ERROR();
    };
    switch (header.type) {
        case FCGI_HEADER_TYPE::STDOUT: {
            unsigned short len = (unsigned short)(header.length[0] << 8 | header.length[1]);
            memset(buf, 0, sizeof(buf));
            if ((read = recv(fd, buf, len, 0)) == -1) {
                THROW_SYSTEM_ERROR();
            };
            std::string str(buf);
            auto f = str.find_first_of("<");
            std::cout << str.substr(f) << std::endl;
            if (header.padding > 0) recv(fd, padding, header.padding, 0);
        }
        break;
        case FCGI_HEADER_TYPE::STDERR: {
            unsigned short len = (unsigned short)(header.length[0] << 8 | header.length[1]);
            memset(buf, 0, sizeof(buf));
            if ((read = recv(fd, buf, len, 0)) == -1) {
                THROW_SYSTEM_ERROR();
            };
            if (header.padding > 0) recv(fd, padding, header.padding, 0);
        }
        break;
        case FCGI_HEADER_TYPE::END_REQUEST: {
            FCGI_END_BODY body;
            if ((read = recv(fd, (char *)&body, sizeof(body), 0)) == -1) {
                THROW_SYSTEM_ERROR();
            };
        }
        break;
        default: {
            
        }
    }
    close(fd);
}
