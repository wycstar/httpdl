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
#include <atomic>

class Worker
{
private:
    std::vector<std::thread> _pool;
    std::queue<std::function<void()>> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::atomic<bool> _stop;
    std::atomic<unsigned int> _num;

public:
    Worker();
    Worker(size_t size);
    ~Worker();
    void stop() {
        _stop.store(true);
    };
    void restart() {
        _stop.store(false);
    };
    unsigned int idle() {
        return _num;
    };
    template<class F, class...Args> //前面是类型 后面是参数
    auto commit(F&& f, Args&&... args)->std::future(decltype(f(args...))); //返回类型后置,一般用在模板
};
