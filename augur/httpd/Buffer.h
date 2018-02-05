#pragma once
#include <memory>

template<typename T>
static std::shared_ptr<T> make_buffer(size_t size) {
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

class Buffer
{
public:
    Buffer();
    ~Buffer();
};
