#include "Worker.h"
#include "log.h"

Worker workers(4);

Worker::Worker()
{
}

Worker::Worker(size_t size):_stop(false)
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
                        return this->_stop.load() || !this->_queue.empty(); //���ֶ�ֹͣ���л��߶��зǿ�ʱ���ټ����ȴ�
                    });
                    if (this->_stop.load() && this->_queue.empty()) return; //���ϲ����ֶ�ֹͣ����Ҫ����������ɺ��ֹͣ����
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

template<class F, class...Args>
auto Worker::commit(F&& f, Args&&... args)->std::future(decltype(f(args...))) {
    if (this->_stop.load()) {
        THROW_SYSTEM_ERROR();
    }
    using ret_type = decltype(f(args));
    auto task = std::make_shared<std::packaged_task<ret_type()>>(   //packaged_task��movable������copy
        std::bind(std::forward<F>f, std::forward<Args>args)...);
    std::future<ret_type> future = task->get_future();
    {
        std::lock_guard<std::mutex> lock{this->_mutex};
        this->_queue.emplace(
            [task]() {
            (*task)();
        }
        );
    }
    this->_cv.notify_one();
    return future;
}