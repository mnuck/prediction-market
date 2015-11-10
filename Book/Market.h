#ifndef MARKET_H
#define MARKET_H

#include <set>
#include <string>

#include "UniqueID.h"

class Market
{
public:
    enum class Status
    {
        OPENED,
        CLOSED,
        DUPLICATE,
        INVALID
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

    const UniqueID&    GetID() const;
    const Status&      GetStatus() const;
    const Outcome&     GetOutcome() const;
    const std::string& GetDescription() const;

    Market& SetStatus(const Status& status);
    Market& SetOutcome(const Outcome& outcome);
    Market& SetDescription(const std::string& description);
    
private:
    UniqueID _id;
    Status _status;
    Outcome  _outcome;
    std::string _description;
    
    std::set<UniqueID> _orders;
    // need to have a data structure where I can sort orders by price and timestamp
};

#endif // MARKET_H
