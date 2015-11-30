#define BOOST_LOG_DYN_LINK 1

#include <memory>
#include <vector>

#include "msgpack.hpp"

#include "Logger.h"
#include "Preferences.h"
#include "WAMPAPI.h"

WAMPAPI::WAMPAPI():
    _requestRouterThread(&WAMPAPI::RequestRouter, this)
{
    RegisterWAMPListeners();
}

WAMPAPI::~WAMPAPI()
{
    _requestRouterThread.interrupt();
    _requestRouterThread.join();
}

std::shared_ptr<Book::Book> WAMPAPI::DerefBook()
{
    std::shared_ptr<Book::Book> pBook = _book.lock();
    if (!pBook)
    {
        LOG(fatal) << "Lost contact with Book";
//        throw "Lost contact with Book";
    }
    return pBook;
}

void WAMPAPI::RegisterDelegate(std::weak_ptr<Book::Book> book)
{
    _book = book;
}

void WAMPAPI::OnBroadcast(const Book::Order& order)
{
    ScopeLog scopelog("WAMPAPI::OnBroadcast(Order)");
    auto realm = prefs.Get("WAMP.Realm", std::string("default"));
    auto topic = realm + ".order.feed";

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);

    pk.pack_array(7);
    pk.pack(order.GetID());
    pk.pack(order.GetMarketID());
    pk.pack(order.GetParticipantID());
    pk.pack(static_cast<unsigned int>(order.GetStatus()));
    pk.pack(static_cast<unsigned int>(order.GetDirection()));
    pk.pack(order.GetQuantity());
    pk.pack(order.GetPrice());

    msgpack::unpacked msg;
    msgpack::unpack(&msg, buffer.data(), buffer.size());

    Broadcast(topic, msg.get());
}

void WAMPAPI::OnBroadcast(const Book::Market& market)
{
    ScopeLog scopelog("WAMPAPI::OnBroadcast(Market)");
    auto realm = prefs.Get("WAMP.Realm", std::string("default"));
    auto topic = realm + ".market.feed";

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);

    pk.pack_array(3);
    pk.pack(market.GetID());
    pk.pack(static_cast<unsigned int>(market.GetStatus()));
    pk.pack(static_cast<unsigned int>(market.GetOutcome()));

    msgpack::unpacked msg;
    msgpack::unpack(&msg, buffer.data(), buffer.size());

    Broadcast(topic, msg.get());
}

void WAMPAPI::OnBroadcast(const Book::Participant& participant)
{
    ScopeLog scopelog("WAMPAPI::OnBroadcast(Participant)");
    auto realm = prefs.Get("WAMP.Realm", std::string("default"));
    auto topic = realm + ".participant.feed";

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);

    pk.pack_array(3);
    pk.pack(participant.GetID());
    pk.pack(static_cast<unsigned int>(participant.GetStatus()));
    pk.pack(participant.GetBalance());

    msgpack::unpacked msg;
    msgpack::unpack(&msg, buffer.data(), buffer.size());

    Broadcast(topic, msg.get());
}

void WAMPAPI::RegisterWAMPListeners()
{
    ScopeLog scopelog(__FUNCTION__);

    using std::make_tuple;
    using ElementType = std::tuple< WAMPAPI::Endpoint, std::string>;
    auto realm = prefs.Get("WAMP.Realm", std::string("default"));
    static const std::vector<ElementType> endpoints
    {
        make_tuple(Endpoint::GET_ID,             realm + ".id"),
        make_tuple(Endpoint::ORDER_OPEN,         realm + ".order.open"),
        make_tuple(Endpoint::ORDER_CLOSE,        realm + ".order.close"),
        make_tuple(Endpoint::MARKET_OPEN,        realm + ".market.open"),
        make_tuple(Endpoint::MARKET_CLOSE,       realm + ".market.close"),
        make_tuple(Endpoint::MARKET_ORDERS,      realm + ".market.orders"),
        make_tuple(Endpoint::MARKET_INDEX,       realm + ".market.index"),
        make_tuple(Endpoint::PARTICIPANT_OPEN,   realm + ".participant.open"),
        make_tuple(Endpoint::PARTICIPANT_CLOSE,  realm + ".participant.close"),
        make_tuple(Endpoint::PARTICIPANT_ORDERS, realm + ".participant.orders"),
        make_tuple(Endpoint::PARTICIPANT_GET,    realm + ".participant.get")
    };

    for (auto& endpoint : endpoints)
    {
        _endpoint.GetSession()->provide(
            std::get<1>(endpoint),
            std::bind(
                &WAMPAPI::EnqueRequest,
                this,
                std::get<0>(endpoint),
                std::placeholders::_1
            )
        );
    }
}

void WAMPAPI::EnqueRequest(WAMPAPI::Endpoint endpoint, 
                           autobahn::wamp_invocation invocation)
{
    auto pBook = DerefBook();
    
    PQElement e;
    e.priority   = 1000;
    e.timestamp  = pBook->GetTimestamp();
    e.endpoint   = endpoint;
    e.invocation = invocation;
    
    if (endpoint == Endpoint::MARKET_CLOSE)
        e.priority = 0;

    _requestQueue.Push(e);
}

void WAMPAPI::RequestRouter()
{
    ScopeLog scopeLog("WAMPAPI::RequestRouter");
    try
    {
        while (true)
        {
            PQElement e = _requestQueue.Pop();
            switch (e.endpoint)
            {
            case Endpoint::GET_ID:
                GetUniqueID(e.invocation);
                break;
            case Endpoint::ORDER_OPEN:
                OpenOrder(e.invocation);
                break;
            case Endpoint::ORDER_CLOSE:
                CloseOrder(e.invocation);
                break;
            case Endpoint::MARKET_OPEN:
                OpenMarket(e.invocation);
                break;
            case Endpoint::MARKET_CLOSE:
                CloseMarket(e.invocation);
                break;
            case Endpoint::MARKET_ORDERS:
                GetOrdersForMarket(e.invocation);
                break;
            case Endpoint::MARKET_INDEX:
                GetMarkets(e.invocation);
                break;
            case Endpoint::PARTICIPANT_OPEN:
                OpenParticipant(e.invocation);
                break;
            case Endpoint::PARTICIPANT_CLOSE:
                CloseParticipant(e.invocation);
                break;
            case Endpoint::PARTICIPANT_ORDERS:
                GetOrdersForParticipant(e.invocation);
                break;
            case Endpoint::PARTICIPANT_GET:
                GetParticipant(e.invocation);
                break;
            default:
                break;
            }
        }
    }
    catch (boost::thread_interrupted const&)
    {
        LOG(trace) << "WAMPAPI::RequestRouter shutting down";
    }
}

void WAMPAPI::GetUniqueID(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);
    auto pBook = DerefBook();
    invocation->result(pBook->GetUniqueID());
}
    
void WAMPAPI::OpenOrder(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);
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
    ScopeLog scopeLog(__FUNCTION__);
}

void WAMPAPI::GetOrdersForMarket(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);
}

void WAMPAPI::GetOrdersForParticipant(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);
}

void WAMPAPI::OpenMarket(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);   
}

void WAMPAPI::CloseMarket(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);    
}

void WAMPAPI::GetMarkets(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);    
}

void WAMPAPI::OpenParticipant(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);    
}

void WAMPAPI::CloseParticipant(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);    
}

void WAMPAPI::GetParticipant(autobahn::wamp_invocation invocation)
{
    ScopeLog scopeLog(__FUNCTION__);    
}
