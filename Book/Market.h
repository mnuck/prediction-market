#ifndef MARKET_H
#define MARKET_H

#include <queue>
#include <set>
#include <string>

#include "Order.h"
#include "UniqueID.h"

namespace Book
{

class Market
{
public:
    enum class Response
    {
        UNINITIALIZED = 0,
        OPENED,
        CLOSED,
        DUPLICATE,
        NO_SUCH_MARKET,
        INVALID_OUTCOME
    };

    enum class Status
    {
        UNINITIALIZED = 0,
        OPENED,
        CLOSED
    };

    enum class Outcome
    {
        UNKNOWN = 0,
        TRUE,
        FALSE
    };

    friend class Book;

    Market();
    Market(const UniqueID& id);
    Market(const Market& rhs);
    ~Market();

    Market& operator=(const Market& rhs);

    const UniqueID&        GetID() const;
    const Market::Status&  GetStatus() const;
    const std::string      GetStatusString() const;
    const Market::Outcome& GetOutcome() const;
    const std::string      GetOutcomeString() const;

    Market& SetStatus(const Market::Status& status);
    Market& SetOutcome(const Market::Outcome& outcome);
    
private:
    UniqueID        _id;
    Market::Status  _status;
    Market::Outcome _outcome;

    std::set<UniqueID> _orders;

    std::priority_queue<Order, std::vector<Order>, Order::CompareBuys>  _buyOrders;
    std::priority_queue<Order, std::vector<Order>, Order::CompareSells> _sellOrders;
};

}
#endif // MARKET_H
