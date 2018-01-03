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

            }
        }
        );
    }
}


Worker::~Worker()
{
}
