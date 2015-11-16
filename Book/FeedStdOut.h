#ifndef FEEDSTDOUT_H
#define FEEDSTDOUT_H

#include "Feed.h" // Base class: Feed

class FeedStdOut : public Feed
{
public:
    FeedStdOut();
    ~FeedStdOut();
    
    void Broadcast(const Book::Order& order);
    void Broadcast(const Book::Market& market);
    void Broadcast(const Book::Participant& participant);
};

#endif // FEEDSTDOUT_H


