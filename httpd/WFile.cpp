#include "WFile.h"
#include <sys/mman.h>

WFile::WFile()
{
}

WFile::WFile(const std::string path):
    _path(path),
    _fd(-1),
    _error_code(HTTPUtil::HTTP_OK),
    _mapped(false)
{
    if (-1 == access(_path.c_str(), F_OK)) {
        _error_code = HTTPUtil::HTTP_NOT_FOUND;
    }
    else {
        _fd = open(_path.c_str(), O_RDONLY);
        if (_fd != -1) {
            fstat(_fd, &_stat);
        }
        else {
            _error_code = HTTPUtil::HTTP_FORBIDDEN;
        }
    }
}

const std::string & WFile::path() const
{
    return _path;
}

char * WFile::data()
{
    _data = reinterpret_cast<char *>(mmap(NULL, _stat.st_size, PROT_READ, MAP_SHARED, _fd, 0));
    _mapped = true;
    return _data;
}

WFile::~WFile()
{
    if (_fd != -1) {
        close(_fd);
    }
    if(_mapped){
        munmap(_data, _stat.st_size);
        _data = nullptr;
    }
}
