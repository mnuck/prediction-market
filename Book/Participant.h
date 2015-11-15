#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <map>
#include <set>
#include <string>

#include "Order.h"
#include "Market.h"
#include "UniqueID.h"

class Participant
{
public:    
    enum class Status
    {
        OPENED,
        CLOSED,
        DUPLICATE,
        NO_SUCH_PARTICIPANT,
        UNINITIALIZED,
        INVALID_ESCROW,
        INVALID_NAME,
        CAN_NOT_CLOSE
    };

    struct MarketStats
    {
        MarketStats(): inventory(0), sellOrderQtySum(0) {}
        int inventory;
        int sellOrderQtySum;
    };
    
    friend class Book;

    Participant();
    Participant(const UniqueID& id);
    Participant(const Participant& rhs);
    ~Participant();

    Participant& operator=(const Participant& rhs);

    const UniqueID&            GetID() const;
    const Participant::Status& GetStatus() const;
    const unsigned int&        GetBalance() const;
    const unsigned int         GetEscrow() const;
    const unsigned int&        GetBuyEscrow() const;
    const unsigned int&        GetCreateEscrow() const;    
    const std::string&         GetName() const;
    const Participant::MarketStats& GetMarketStats(const UniqueID& marketID) const;

    Participant& SetStatus(const Participant::Status& status);
    Participant& SetBalance(const unsigned int& balance);
    Participant& SetName(const std::string& name);

private:
    UniqueID            _id;
    Participant::Status _status;
    unsigned int        _balance;
    unsigned int        _buyEscrow;
    unsigned int        _createEscrow;
    std::string         _name;
    
    std::set<UniqueID> _orders;
    
    std::map<UniqueID, MarketStats> _marketStats;
    
    static const MarketStats _dummyMarketStats;
};

#endif // PARTICIPANT_H
