#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include "boost/thread.hpp"

template<typename ContainerType>
class WorkQueue
{
public:
    void Push(const typename ContainerType::value_type& item)
    {
        boost::mutex::scoped_lock lock(_mutex);
        _queue.push(item);
        lock.unlock();
        _cv.notify_one();
    }
    
    typename ContainerType::value_type Pop()
    {
        boost::mutex::scoped_lock lock(_mutex);   
        typename ContainerType::value_type result;
        while (_queue.empty())
        {
            _cv.wait(lock);
        }
        result = _queue.top();
        _queue.pop();
        return result;
    }
    
private:
    ContainerType _queue;
    boost::condition_variable _cv;
    mutable boost::mutex      _mutex;
};


#endif // WORK_QUEUE_H
