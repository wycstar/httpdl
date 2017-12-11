#pragma once

#include <string.h>
#include <system_error>
#include <cerrno>
#include <iostream>

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : (__FILE__))

#define _ERROR(msg) \ 
    std::cerr << "[ERROR]" << __FILENAME__ << ":" << __LINE__ << " " << msg << std::endl;

#define _WARNING(msg) \ 
    std::cerr << "[WARNING]" << __FILENAME__ << ":" << __LINE__ << " " << msg << std::endl;

#define _INFO(msg) \ 
    std::cerr << "[INFO]" << __FILENAME__ << ":" << __LINE__ << " " << msg << std::endl;

#define SYSTEM_ERROR() \
do { \
	_ERROR(strerror(errno)); \
} while (0)

#define THROW_SYSTEM_ERROR() \
do { \
    SYSTEM_ERROR(); \
    throw std::system_error(std::error_code(errno, std::system_category())); \
} while (0)
