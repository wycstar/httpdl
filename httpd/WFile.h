#pragma once
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

class WFile
{
private:
    std::string _path;
    size_t _size;
    int _fd;

public:
    WFile();
    WFile(const std::string path);
    const std::string & path() const;
    ~WFile();
};
