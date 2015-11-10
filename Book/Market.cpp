#include "Market.h"

Market::Market():
    _id(0)
{
}

Market::Market(const UniqueID& id):
    _id(id),
    _status(Market::Status::INVALID),
    _outcome(Market::Outcome::UNKNOWN),
    _description("")
{
}

Market::Market(const Market& rhs):
    _id(rhs._id),
    _status(rhs._status),
    _outcome(rhs._outcome),
    _description(rhs._description)
{
}

Market::~Market()
{
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

const std::string& Market::GetDescription() const
{
    return _description;
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

Market& Market::SetDescription(const std::string& description)
{
    _description = description;
    return *this;
}
