#include "Worker.h"
#include "log.h"

Worker::Worker()
{
}

Worker::Worker(unsigned int size):_stop(false)
{
    _num = size < 1 ? 1 : size;
    for (size = 0; size < _num; size++) {
        _pool.emplace_back(
            [this] {
            while (!this->_stop.load()) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock{ this->_mutex };
                    this->_cv.wait(lock,
                        [this] {
                        return this->_stop.load() || !this->_queue.empty(); //当手动停止运行或者队列非空时不再继续等待
                    });
                    if (this->_stop.load() && this->_queue.empty()) return; //接上步，手动停止后需要所有任务都完成后才停止运行
                    task = std::move(this->_queue.front());
                    this->_queue.pop();
                    this->_num--;
                    task();
                    this->_num++;
                }
            }
        }
        );
    }
}

Worker::~Worker()
{
    {
        std::unique_lock<std::mutex> lock{ this->_mutex };
        _stop = true;
    }
    _cv.notify_all();
    for (std::thread &t:_pool) {
        t.join();
    }
}
