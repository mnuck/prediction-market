#ifndef BROADCASTOBSERVABLE_H
#define BROADCASTOBSERVABLE_H

#include <memory>
#include <vector>

#include "BroadcastObserver.h"

class BroadcastObservable
{
public:
    void RegisterBroadcastObserver(std::weak_ptr<BroadcastObserver> pBL);
    
protected:
    void Broadcast(const Book::Order& order);
    void Broadcast(const Book::Market& market);
    void Broadcast(const Book::Participant& participant);

    std::vector<std::weak_ptr<BroadcastObserver> > _observers;
};

#endif // BROADCASTOBSERVABLE_H
