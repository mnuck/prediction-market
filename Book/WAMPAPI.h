#ifndef WAMPAPI_H
#define WAMPAPI_H

#include <stdint.h>

#include <autobahn/autobahn.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "BroadcastObserver.h"
#include "Book.h"
#include "Market.h"
#include "Order.h"
#include "Participant.h"

class WAMPAPI : public BroadcastObserver
{
public:
    WAMPAPI(Book::Book& book);
    ~WAMPAPI();

    virtual void OnBroadcast(const Book::Order& order);
    virtual void OnBroadcast(const Book::Market& market);
    virtual void OnBroadcast(const Book::Participant& participant);
    
    void GetUniqueID(autobahn::wamp_invocation invocation);
    
    void OpenOrder(autobahn::wamp_invocation invocation);
    void CloseOrder(autobahn::wamp_invocation invocation);

    void GetMarkets(autobahn::wamp_invocation invocation);
    void OpenMarket(autobahn::wamp_invocation invocation);
    void CloseMarket(autobahn::wamp_invocation invocation);

    void GetOrdersForParticipant(autobahn::wamp_invocation invocation);
    void GetOrdersForMarket(autobahn::wamp_invocation invocation);

    void OpenParticipant(autobahn::wamp_invocation invocation);
    void CloseParticipant(autobahn::wamp_invocation invocation);
    void GetParticipant(autobahn::wamp_invocation invocation);

protected:
    void Connect();
    void RegisterWAMPListeners();
    
    template <typename T>
    void Broadcast(std::string topic, T args);

    const std::string _feedTopic;
    const std::string _realm;
    const std::string _ipAddr;
    const uint16_t    _ipPort;
    
    Book::Book& _book;

    bool _ready;
    boost::thread _thread;
    boost::asio::io_service _io;
    std::shared_ptr<autobahn::wamp_session> _session;
    std::shared_ptr<autobahn::wamp_tcp_transport> _transport;
    
    boost::condition_variable _cvReady;
    boost::mutex _cvm;
};

#include "WAMPAPI.hpp"

#endif // WAMPAPI_H
