#include "Worker.h"

Worker::Worker()
{
}

Worker::Worker(size_t size):_stop(false)
{
    _num = size < 1 ? 1 : size;
    for (size = 0; size < _num; size++) {
        _pool.emplace_back(
            [this] {
            while (!this->_stop) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock{ this->_mutex };
                    this->_cv.wait(lock,
                        [this] {
                        return this->_stop.load() || !this->_queue.empty(); //���ֶ�ֹͣ���л��߶��зǿ�ʱ���ټ����ȴ�
                    });
                    if (this->_stop && this->_queue.empty()) return; //���ϲ����ֶ�ֹͣ����Ҫ����������ɺ��ֹͣ����
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
}
