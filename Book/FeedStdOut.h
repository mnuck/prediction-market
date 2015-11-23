#ifndef FEEDSTDOUT_H
#define FEEDSTDOUT_H

#include "BroadcastObserver.h"

class FeedStdOut : public BroadcastObserver
{
public:
    FeedStdOut();
    ~FeedStdOut();
    
    virtual void OnBroadcast(const Book::Order& order);
    virtual void OnBroadcast(const Book::Market& market);
    virtual void OnBroadcast(const Book::Participant& participant);
};

#endif // FEEDSTDOUT_H


