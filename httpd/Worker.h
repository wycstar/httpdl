#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class Worker
{
private:
    std::vector<std::thread> _pool;
    std::queue<std::function<void()>> _queue;
    std::mutex _mutex;


public:
    Worker();
    Worker(size_t size);
    ~Worker();
};
