#pragma once
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "HTTPUtil.h"

class WFile
{
private:
    std::string _path;
    size_t _size;
    int _fd;
    HTTPUtil::HTTP_STATUS_CODE _error_code;
    struct stat _stat;
    char * _data;
    bool _mapped;

public:
    WFile();
    WFile(const std::string path);
    const std::string & path() const;
    bool is_dir() const {
        return S_ISDIR(_stat.st_mode);
    };
    bool is_executable() const {
        return (_stat.st_mode & S_IXUSR) || (_stat.st_mode & S_IXGRP) || (_stat.st_mode & S_IXOTH);
    };
    HTTPUtil::HTTP_STATUS_CODE error() const {
        return _error_code;
    };
    const size_t size() const{
        return _stat.st_size;
    };
    char *data();
    static bool is_exists(std::string &name);
    ~WFile();
};
