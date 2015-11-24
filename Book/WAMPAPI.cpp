#define BOOST_LOG_DYN_LINK 1

#include <memory>

#include "Logger.h"
#include "WAMPAPI.h"
#include "UniqueID.h"

#include <boost/log/trivial.hpp>

using namespace boost::asio;
using boost::future;

WAMPAPI::WAMPAPI(Book::Book& book):
    _ipAddr("127.0.0.1"),
    _ipPort(8090),
    _book(book),
    _ready(false),
    _thread(&WAMPAPI::Connect, this)
{
    boost::unique_lock<boost::mutex> lock(_cvm);
    while (!_ready)
        _cvReady.wait(lock);
        
    _book.RegisterBroadcastObserver(std::shared_ptr<WAMPAPI>(this));
}

WAMPAPI::~WAMPAPI()
{
    _io.stop();
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void WAMPAPI::Connect()
{
    ScopeLog scopelog(__FUNCTION__);
    bool debug = false;
    _session = std::make_shared<autobahn::wamp_session>(_io, debug);

    ip::tcp::endpoint endpoint(ip::address::from_string(_ipAddr), _ipPort);

    _transport = std::make_shared<autobahn::wamp_tcp_transport>(
        _io, endpoint, debug);

    _transport->attach(
        std::static_pointer_cast<autobahn::wamp_transport_handler>(_session));

    future<void> connect_future;
    future<void> start_future;
    future<void> join_future;

    try 
    {
        connect_future = _transport->connect().then(
            [&](future<void> connected) {
                connected.get();
            
                LOG(trace) << "transport connected";
            
                start_future = _session->start().then(
                    [&](future<void> started) {
                        started.get();
                    
                        LOG(trace) << "session started";
                    
                        join_future = _session->join(_realm).then(
                            [&](future<uint64_t> joined) {
                            
                                LOG(trace) << "joined realm: " 
                                                         << joined.get();
                            
                                RegisterWAMPListeners();

                                boost::lock_guard<boost::mutex> lock(_cvm);
                                _ready = true;
                                _cvReady.notify_all();
                            });
                    });
            });

    } 
    catch (const std::exception& e)
    {
        LOG(error) << __FUNCTION__ 
                   << " caught exception: "
                   << e.what();
        _io.stop();
        return;
    }

    LOG(trace) << "starting io service";
    _io.run();
    LOG(trace) << "stopped io service";
}


void WAMPAPI::OnBroadcast(const Book::Order& order)
{
    auto topic = "com.nuckdev.prediction-market.order.feed";
    auto args = std::make_tuple
    (
        order.GetID(),
        order.GetMarketID(),
        order.GetStatusString(),
        order.GetDirectionString(),
        order.GetQuantity(),
        order.GetPrice()
    );

    Broadcast(topic, args);
}

void WAMPAPI::OnBroadcast(const Book::Market& market)
{
    auto topic = "com.nuckdev.prediction-market.market.feed";
    auto args = std::make_tuple
    (
        market.GetID(),
        market.GetStatusString(),
        market.GetOutcomeString()
    );

    Broadcast(topic, args);
}

void WAMPAPI::OnBroadcast(const Book::Participant& participant)
{
    auto topic = "com.nuckdev.prediction-market.participant.feed";
    auto args = std::make_tuple
    (
        participant.GetID(),
        participant.GetStatusString(),
        participant.GetBalance()
    );

    Broadcast(topic, args);
}


void WAMPAPI::GetUniqueID(autobahn::wamp_invocation invocation)
{
    invocation->result(_book.GetUniqueID());
}
    
void WAMPAPI::OpenOrder(autobahn::wamp_invocation invocation)
{
    Book::UniqueID orderID;
    Book::UniqueID participantID;
    Book::UniqueID marketID;
    unsigned int uiDirection;
    unsigned int quantity;
    unsigned int price;
    invocation->get_each_argument(orderID, participantID, marketID, uiDirection, quantity, price);
    
    
}

void WAMPAPI::CloseOrder(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::GetOrdersForMarket(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::GetOrdersForParticipant(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::OpenMarket(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::CloseMarket(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::GetMarkets(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::OpenParticipant(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::CloseParticipant(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::GetParticipant(autobahn::wamp_invocation invocation)
{
    
}

void WAMPAPI::RegisterWAMPListeners()
{
    ScopeLog scopelog(__FUNCTION__);
    namespace ph = std::placeholders;
    _session->provide(std::string("com.nuckdev.prediction-market.id"),
                      std::bind(&WAMPAPI::GetUniqueID, this, ph::_1)).get();


    _session->provide(std::string("com.nuckdev.prediction-market.order.open"),
                      std::bind(&WAMPAPI::OpenOrder, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.order.close"),
                      std::bind(&WAMPAPI::CloseOrder, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.market.open"),
                      std::bind(&WAMPAPI::OpenMarket, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.market.close"),
                      std::bind(&WAMPAPI::CloseMarket, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.market.orders"),
                      std::bind(&WAMPAPI::GetOrdersForMarket, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.participant.orders"),
                      std::bind(&WAMPAPI::GetOrdersForParticipant, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.market.index"),
                      std::bind(&WAMPAPI::GetMarkets, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.participant.open"),
                      std::bind(&WAMPAPI::OpenParticipant, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.participant.close"),
                      std::bind(&WAMPAPI::CloseParticipant, this, ph::_1)).get();

    _session->provide(std::string("com.nuckdev.prediction-market.participant.get"),
                      std::bind(&WAMPAPI::GetOrdersForParticipant, this, ph::_1)).get();
}
