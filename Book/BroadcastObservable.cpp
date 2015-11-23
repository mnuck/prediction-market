#include "BroadcastObservable.h"


void BroadcastObservable::RegisterBroadcastObserver(std::weak_ptr<BroadcastObserver> pBL)
{
    _observers.push_back(pBL);
}

void BroadcastObservable::Broadcast(const Book::Order& order)
{
    for (auto& wPtr : _observers)
    {
        auto sPtr = wPtr.lock();
        if (sPtr)
            sPtr->OnBroadcast(order);
    }
}

void BroadcastObservable::Broadcast(const Book::Market& market)
{
    for (auto& wPtr : _observers)
    {
        auto sPtr = wPtr.lock();
        if (sPtr)
            sPtr->OnBroadcast(market);
    }
}

void BroadcastObservable::Broadcast(const Book::Participant& participant)
{
    for (auto& wPtr : _observers)
    {
        auto sPtr = wPtr.lock();
        if (sPtr)
            sPtr->OnBroadcast(participant);
    }    
}
