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
    Worker(unsigned int size);
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
    template<class F, class...Args> //ǰ�������� �����ǲ���,ע�ⲻҪ���������ʵ��
    auto commit(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> { //�������ͺ���,һ������ģ��
        using ret_type = typename std::result_of<F(Args...)>::type;;
        auto task = std::make_shared<std::packaged_task<ret_type()>>(   //packaged_task��movable������copy
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<ret_type> future = task->get_future();
        {
            std::lock_guard<std::mutex> lock{ this->_mutex };
            this->_queue.emplace(
                [task]() {
                (*task)();
            });
        }
        this->_cv.notify_one();
        return future;
    };
};
