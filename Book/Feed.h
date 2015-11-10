#ifndef FEED_H
#define FEED_H

#include <Market.h>
#include <Order.h>
#include <Participant.h>

class Feed
{
public:
    Feed();
    ~Feed();
    
    void Broadcast(const Order& order);
    void Broadcast(const Market& market);
    void Broadcast(const Participant& participant);
};

#endif // FEED_H
