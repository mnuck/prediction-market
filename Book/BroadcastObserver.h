#ifndef BROADCASTLISTENER_H
#define BROADCASTLISTENER_H

#include "Market.h"
#include "Order.h"
#include "Participant.h"

class BroadcastObserver
{
public:
    virtual void OnBroadcast(const Book::Order& order) = 0;
    virtual void OnBroadcast(const Book::Market& market) = 0;
    virtual void OnBroadcast(const Book::Participant& participant) = 0;
};

#endif // BROADCASTLISTENER_H
