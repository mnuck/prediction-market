#ifndef WAMPAPI_H
#define WAMPAPI_H

#include <functional>

#include <autobahn/autobahn.hpp>
#include <boost/thread.hpp>
#include <msgpack.hpp>

#include "BroadcastObserver.h"
#include "Book.h"
#include "Market.h"
#include "Order.h"
#include "Participant.h"
#include "WorkQueue.hpp"
#include "WAMPEndpoint.h"


class WAMPAPI:
    public BroadcastObserver
{
public:
    enum class Endpoint
    {
        GET_ID,
        ORDER_OPEN,
        ORDER_CLOSE,
        MARKET_OPEN,
        MARKET_CLOSE,
        MARKET_ORDERS,
        MARKET_INDEX,
        PARTICIPANT_OPEN,
        PARTICIPANT_CLOSE,
        PARTICIPANT_ORDERS,
        PARTICIPANT_GET
    };

    WAMPAPI();
    virtual ~WAMPAPI();
    
    void RegisterDelegate(std::weak_ptr<Book::Book> book);

    virtual void OnBroadcast(const Book::Market& market);
    virtual void OnBroadcast(const Book::Order& order);
    virtual void OnBroadcast(const Book::Participant& participant);

    void EnqueRequest(WAMPAPI::Endpoint endpoint, 
                      autobahn::wamp_invocation invocation);

protected:
    virtual void RegisterWAMPListeners();
    void RequestRouter();

    void GetUniqueID(autobahn::wamp_invocation invocation);

    void OpenOrder(autobahn::wamp_invocation invocation);
    void CloseOrder(autobahn::wamp_invocation invocation);

    void OpenMarket(autobahn::wamp_invocation invocation);
    void CloseMarket(autobahn::wamp_invocation invocation);
    void GetOrdersForMarket(autobahn::wamp_invocation invocation);
    void GetMarkets(autobahn::wamp_invocation invocation);

    void OpenParticipant(autobahn::wamp_invocation invocation);
    void CloseParticipant(autobahn::wamp_invocation invocation);
    void GetOrdersForParticipant(autobahn::wamp_invocation invocation);
    void GetParticipant(autobahn::wamp_invocation invocation);

    template <typename T>
    void Broadcast(std::string topic, T args);
    
    
    msgpack::object BuildMsgPackObject(
        std::function<void (msgpack::packer<msgpack::sbuffer>&)> f);

    std::shared_ptr<Book::Book> DerefBook();

    struct NullDeleter
    {
        template <typename T>
        void operator()(T*) {}
    };

    struct PQElement
    {
        bool operator()(const PQElement& lhs, const PQElement& rhs)
        {
            if (lhs.priority == rhs.priority)
                return lhs.timestamp > rhs.timestamp;
            return lhs.priority > rhs.priority;
        }

        unsigned int      priority;  // smaller is sooner
        Book::UniqueID    timestamp; // smaller is sooner
        WAMPAPI::Endpoint endpoint;
        autobahn::wamp_invocation invocation;
    };

    using QueueType =
        std::priority_queue<PQElement,
                            std::vector<PQElement>,
                            PQElement>;
    
    std::weak_ptr<Book::Book> _book;
    WorkQueue<QueueType> _requestQueue;
    boost::thread _requestRouterThread;
    WAMPEndpoint _endpoint;
};

#include "WAMPAPI.hpp"

#endif // WAMPAPI_H
