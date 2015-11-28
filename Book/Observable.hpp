#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <memory>
#include <vector>

#include "Observer.hpp"

template <typename T>
class Observable
{
public:
    Observable(): _obsCount(0) {}
//    virtual void RegisterObserver(std::weak_ptr<Observer<T> > pObserver);
    virtual void RegisterObserver(Observer<T>* pObserver);

protected:
    virtual void Notify(const T& notification);
    
//    std::vector<std::weak_ptr<Observer<T> > > _observers;
    std::vector<Observer<T>*> _observers;
    unsigned int _obsCount;
};

#include "Observable.ipp"

#endif // OBSERVABLE_HPP
