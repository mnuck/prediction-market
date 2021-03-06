#include "Participant.h"

using Book::UniqueID;
using Book::Participant;

const Participant::MarketStats Participant::_dummyMarketStats;

Participant::Participant():
    _id(0),
    _status(Participant::Status::UNINITIALIZED),
    _balance(0),
    _buyEscrow(0),
    _createEscrow(0)
{
}

Participant::Participant(const UniqueID& id):
    _id(id),
    _status(Participant::Status::UNINITIALIZED),
    _balance(0),
    _buyEscrow(0),
    _createEscrow(0)
{
}

Participant::Participant(const Participant& rhs):
    _id(rhs._id),
    _status(rhs._status),
    _balance(rhs._balance),
    _buyEscrow(rhs._buyEscrow),
    _createEscrow(rhs._createEscrow)
{
}

Participant::~Participant()
{
}

Participant& Participant::operator=(const Participant& rhs)
{
    _id         = rhs._id;
    _status     = rhs._status;
    _balance    = rhs._balance;
    _buyEscrow  = rhs._buyEscrow;
    _createEscrow = rhs._createEscrow;
    
    return *this;
}


const UniqueID& Participant::GetID() const
{
    return _id;
}

const Participant::Status& Participant::GetStatus() const
{
    return _status;
}

const unsigned int& Participant::GetBalance() const
{
    return _balance;
}

const unsigned int Participant::GetEscrow() const
{
    return _buyEscrow + _createEscrow;
}

const unsigned int& Participant::GetBuyEscrow() const
{
    return _buyEscrow;
}

const unsigned int& Participant::GetCreateEscrow() const
{
    return _createEscrow;
}

const Participant::MarketStats& Participant::GetMarketStats(const UniqueID& marketID) const
{
    auto msIter = _marketStats.find(marketID);
    if (msIter == _marketStats.end())
        return _dummyMarketStats;
    return msIter->second;
}

Participant& Participant::SetStatus(const Status& status)
{
    _status = status;
    return *this;
}

Participant& Participant::SetBalance(const unsigned int& balance)
{
    _balance = balance;
    return *this;
}

const std::vector<std::string>& Book::Participant::GetResponseStrings()
{
    static std::vector<std::string> result
    {
        "Uninitialized",
        "Opened",
        "Closed",
        "Duplicate",
        "No Such Participant",
        "Invalid Escrow",
        "Can Not Close"
    };
    return result;
}

const std::vector<std::string>& Book::Participant::GetStatusStrings()
{
    static std::vector<std::string> result
    {
        "Uninitialized",
        "Opened",
        "Closed"
    };
    return result;
}
