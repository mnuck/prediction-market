#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <map>
#include <set>
#include <string>

#include "UniqueID.h"

class Participant
{
public:
    enum class Status
    {
        OPENED,
        CLOSED,
        DUPLICATE,
        INVALID,
        CAN_NOT_CLOSE
    };
    
    friend class Book;

    Participant();
    Participant(const UniqueID& id);
    Participant(const Participant& rhs);
    ~Participant();

    Participant& operator=(const Participant& rhs);

    const UniqueID&     GetID() const;
    const Status&       GetStatus() const;
    const unsigned int& GetBalance() const;
    const unsigned int& GetEscrow() const;
    const std::string&  GetName() const;

    Participant& SetStatus(const Status& status);
    Participant& SetBalance(const unsigned int& balance);
    Participant& SetEscrow(const unsigned int& escrow);
    Participant& SetName(const std::string& name);    

private:
    UniqueID     _id;
    Status       _status;
    unsigned int _balance;
    unsigned int _buyEscrow;
    unsigned int _sellEscrow;
    std::string  _name;
    
    std::set<UniqueID> _orders;
    
    struct MarketStats
    {
        MarketStats():
            inventory(0), sellOrderQtySum(0), sellOrderValueSum(0),
            buyOrderQtySum(0), buyOrderPriceSum(0) {}
            
        int inventory;
        int sellOrderQtySum;
        int sellOrderValueSum;
        int buyOrderQtySum;
        int buyOrderPriceSum;
    };
    std::map<UniqueID, MarketStats> _marketStats; // key is marketID
};

#endif // PARTICIPANT_H
