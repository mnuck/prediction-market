#include "Market.h"

using Book::UniqueID;
using Book::Market;

Market::Market():
    _id(0),
    _status(Market::Status::UNINITIALIZED),
    _outcome(Market::Outcome::UNKNOWN)
{
}

Market::Market(const UniqueID& id):
    _id(id),
    _status(Market::Status::UNINITIALIZED),
    _outcome(Market::Outcome::UNKNOWN)
{
}

Market::Market(const Market& rhs):
    _id(rhs._id),
    _status(rhs._status),
    _outcome(rhs._outcome)
{
}

Market::~Market()
{
}

Market& Market::operator=(const Market& rhs)
{
    _id = rhs._id;
    _status = rhs._status;
    _outcome = rhs._outcome;
    
    return *this;
}


const UniqueID& Market::GetID() const
{
    return _id;
}

const Market::Status& Market::GetStatus() const
{
    return _status;
}

const Market::Outcome& Market::GetOutcome() const
{
    return _outcome;
}

Market& Market::SetStatus(const Market::Status& status)
{
    _status = status;
    return *this;
}

Market& Market::SetOutcome(const Market::Outcome& outcome)
{
    _outcome = outcome;
    return *this;
}

const std::vector<std::string>& Book::Market::GetResponseStrings()
{
    static std::vector<std::string> result
    {
        "Uninitialized",
        "Opened",
        "Closed",
        "Duplicate",
        "No Such Market",
        "Invalid Outcome"
    };
    return result;
}

const std::vector<std::string>& Book::Market::GetStatusStrings()
{
    static std::vector<std::string> result
    {
        "Uninitialized",
        "Opened",
        "Closed"
    };
    return result;
}

const std::vector<std::string>& Book::Market::GetOutcomeStrings()
{
    static std::vector<std::string> result
    {
        "Unknown",
        "True",
        "False"
    };
    return result;
}
