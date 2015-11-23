#ifndef WAMPAPI_H
#define WAMPAPI_H

#include <autobahn/autobahn.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "BroadcastObserver.h"

#include "Market.h"
#include "Order.h"
#include "Participant.h"

class WAMPAPI : public BroadcastObserver
{
public:
    WAMPAPI();
    ~WAMPAPI();

    virtual void OnBroadcast(const Book::Order& order);
    virtual void OnBroadcast(const Book::Market& market);
    virtual void OnBroadcast(const Book::Participant& participant);

protected:
    void Connect();

    bool _ready;
    boost::thread _thread;
    boost::asio::io_service _io;
    std::shared_ptr<autobahn::wamp_session> _session;
    std::shared_ptr<autobahn::wamp_tcp_transport> _transport;
    
    boost::condition_variable _cvReady;
    boost::mutex _cvm;
};

#endif // WAMPAPI_H
