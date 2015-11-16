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
    
    virtual void Broadcast(const Book::Order& order);
    virtual void Broadcast(const Book::Market& market);
    virtual void Broadcast(const Book::Participant& participant);
};

#endif // FEED_H
