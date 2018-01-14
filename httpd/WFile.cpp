#include "WFile.h"
#include <sys/mman.h>

WFile::WFile()
{
}

WFile::WFile(const std::string path):
    _path(path),
    _fd(-1),
    _error_code(HTTP_OK),
    _mapped(false)
{
    _fd = open(_path.c_str(), O_RDONLY);
    std::cout << _path << std::endl;
    std::cout << errno << std::endl;
    std::cout << _fd << std::endl;
    switch (errno) {
    case ENOENT:
        _error_code = HTTP_NOT_FOUND;
        break;
    case EACCES:
        _error_code = HTTP_FORBIDDEN;
    case 0:
        fstat(_fd, &_stat);
        break;
    }
}

const std::string & WFile::path() const
{
    return _path;
}

char * WFile::data()
{
    //_data = reinterpret_cast<char *>(mmap(NULL, _stat.st_size, PROT_READ, MAP_SHARED, _fd, 0));
    _mapped = true;
    return _data;
}

WFile::~WFile()
{
    std::cout << _fd << "\t" << _mapped << std::endl;
    if (_fd != -1) {
        close(_fd);
    }
    if(_mapped){
        munmap(_data, _stat.st_size);
        _data = nullptr;
    }
}
