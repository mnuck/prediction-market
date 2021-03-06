#ifndef FEEDWAMP_H
#define FEEDWAMP_H

#include <autobahn/autobahn.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "BroadcastObserver.h"

class FeedWAMP : public BroadcastObserver
{
public:
    FeedWAMP();
    ~FeedWAMP();

    virtual void OnBroadcast(const Book::Order& order);
    virtual void OnBroadcast(const Book::Market& market);
    virtual void OnBroadcast(const Book::Participant& participant);

    void Connect();
protected:

    bool _ready;
    boost::thread _thread;
    boost::asio::io_service _io;
    std::shared_ptr<autobahn::wamp_session> _session;
    std::shared_ptr<autobahn::wamp_tcp_transport> _transport;
    
    boost::condition_variable _cvReady;
    boost::mutex _cvm;
};

#endif // FEEDWAMP_H
