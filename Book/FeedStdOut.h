#ifndef FEEDSTDOUT_H
#define FEEDSTDOUT_H

#include "Feed.h" // Base class: Feed

class FeedStdOut : public Feed
{
public:
    FeedStdOut();
    ~FeedStdOut();
    
    void Broadcast(const Order& order);
    void Broadcast(const Market& market);
    void Broadcast(const Participant& participant);
};

#endif // FEEDSTDOUT_H


