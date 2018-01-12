#include "WFile.h"

WFile::WFile()
{
}

WFile::WFile(const std::string path):
    _path(path)
{
    _fd = open(_path.c_str(), O_RDONLY);
}

const std::string & WFile::path() const
{
    return _path;
}

WFile::~WFile()
{
}
