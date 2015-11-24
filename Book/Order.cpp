#include "Order.h"

using Book::UniqueID;
using Book::Order;

Order::Order():
    _id(0),
    _participantID(0),
    _marketID(0),
    _timestamp(0),
    _status(Order::Status::UNINITIALIZED),
    _quantity(0),
    _price(0),
    _direction(Order::Direction::BUY)
{
}

Order::~Order()
{
}

Order::Order(const UniqueID& id):
    _id(id),
    _participantID(0),
    _marketID(0),
    _timestamp(0),
    _status(Order::Status::UNINITIALIZED),
    _quantity(0),
    _price(0),
    _direction(Order::Direction::BUY)
{
}

Order::Order(const Order& rhs):
    _id(rhs._id),
    _participantID(rhs._participantID),
    _marketID(rhs._marketID),
    _timestamp(rhs._timestamp),
    _status(rhs._status),
    _quantity(rhs._quantity),
    _price(rhs._price),
    _direction(rhs._direction)
{}

bool Order::CompareBuys::operator()(const Order& lhs, const Order& rhs)
{
    if (lhs._price == rhs._price)
        return lhs._timestamp > rhs._timestamp;
    return lhs._price < rhs._price;
}

bool Order::CompareSells::operator()(const Order& lhs, const Order& rhs)
{
    if (lhs._price == rhs._price)
        return lhs._timestamp > rhs._timestamp;
    return lhs._price > rhs._price;
}


Order& Order::operator=(const Order& rhs)
{
    _id            = rhs._id;
    _participantID = rhs._participantID;
    _marketID      = rhs._marketID;
    _timestamp     = rhs._timestamp;
    _status        = rhs._status;
    _quantity      = rhs._quantity;
    _price         = rhs._price;
    _direction     = rhs._direction;
    
    return *this;
}

const UniqueID& Order::GetID() const
{
    return _id;
}

const UniqueID& Order::GetParticipantID() const
{
    return _participantID;
}

const UniqueID& Order::GetMarketID() const
{
    return _marketID;
}

const Order::Status& Order::GetStatus() const
{
    return _status;
}

const unsigned int& Order::GetQuantity() const
{
    return _quantity;
}

const unsigned int& Order::GetPrice() const
{
    return _price;
}

const Order::Direction& Order::GetDirection() const
{
    return _direction;
}

Order& Order::SetParticipantID(const UniqueID& participantID)
{
    _participantID = participantID;
    return *this;
}

Order& Order::SetMarketID(const UniqueID& marketID)
{
    _marketID = marketID;
    return *this;
}

Order& Order::SetStatus(const Order::Status& status)
{
    _status = status;
    return *this;
}

Order& Order::SetQuantity(const unsigned int& quantity)
{
    _quantity = quantity;
    return *this;
}

Order& Order::SetPrice(const unsigned int& price)
{
    _price = price;
    return *this;
}

Order& Order::SetDirection(const Order::Direction& direction)
{
    _direction = direction;
    return *this;
}

const std::string Order::GetStatusString() const
{
    switch (_status)
    {
    case Status::OPENED:
        return "Opened";
        break;
    case Status::CLOSED:
        return "Closed";
        break;
    case Status::PARTIAL_FILLED:
        return "Partial Filled";
        break;
    case Status::FILLED:
        return "Filled";
        break;
    case Status::DUPLICATE:
        return "Duplicate";
        break;
    case Status::NO_SUCH_ORDER:
        return "No Such Order";
        break;
    case Status::UNINITIALIZED:
        return "Uninitialized";
        break;
    case Status::INVALID_QUANTITY:
        return "Invalid Outcome";
        break;
    case Status::INVALID_MARKET:
        return "Invalid Market";
        break;
    case Status::INVALID_PARTICIPANT:
        return "Invalid Participant";
        break;
    case Status::INSUFFICIENT_BALANCE:
        return "Insufficient Balance";
    default:
        return "Undefined Order Status";
        break;
    }
}

const std::string Order::GetDirectionString() const
{
    switch (_direction)
    {
    case Direction::BUY:
        return "Buy";
        break;
    case Direction::SELL:
        return "Sell";
        break;
    default:
        return "Undefined Order Direction";
        break;
    }
}
