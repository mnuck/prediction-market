#ifndef MARKET_H
#define MARKET_H

#include <queue>
#include <set>
#include <string>
#include <vector>

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
    
    static const std::vector<std::string>& GetResponseStrings();

    enum class Status
    {
        UNINITIALIZED = 0,
        OPENED,
        CLOSED
    };
    static const std::vector<std::string>& GetStatusStrings();

    enum class Outcome
    {
        UNKNOWN = 0,
        TRUE,
        FALSE
    };
    static const std::vector<std::string>& GetOutcomeStrings();

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

}
#endif // MARKET_H
