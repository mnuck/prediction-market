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

const std::string Book::Market::GetStatusString() const
{
    switch (_status)
    {
    case Status::OPENED:
        return "Opened";
        break;
    case Status::CLOSED:
        return "Closed";
        break;
    case Status::DUPLICATE:
        return "Duplicate";
        break;
    case Status::NO_SUCH_MARKET:
        return "No Such Market";
        break;
    case Status::UNINITIALIZED:
        return "Uninitialized";
        break;
    case Status::INVALID_OUTCOME:
        return "Invalid Outcome";
        break;
    default:
        return "Undefined Market Status";
        break;
    }
}

const std::string Book::Market::GetOutcomeString() const
{
    switch (_outcome)
    {
    case Outcome::TRUE:
        return "True";
        break;
    case Outcome::FALSE:
        return "False";
        break;
    case Outcome::UNKNOWN:
        return "Unknown";
        break;
    default:
        return "Undefined Market Status";
        break;
    }
}
