#ifndef MARKET_H
#define MARKET_H

#include <queue>
#include <set>
#include <string>

#include "Order.h"
#include "UniqueID.h"

class Market
{
public:
    enum class Status
    {
        OPENED,
        CLOSED,
        DUPLICATE,
        NO_SUCH_MARKET,
        UNINITIALIZED,
        INVALID_OUTCOME
    };
    
    enum class Outcome
    {
        TRUE,
        FALSE,
        UNKNOWN
    };
    
    friend class Book;

    Market();
    Market(const UniqueID& id);
    Market(const Market& rhs);
    ~Market();

    Market& operator=(const Market& rhs);

    const UniqueID&        GetID() const;
    const Market::Status&  GetStatus() const;
    const Market::Outcome& GetOutcome() const;

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

#endif // MARKET_H
