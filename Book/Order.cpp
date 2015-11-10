#include "Order.h"

Order::Order():
    _id(0)
{
}

Order::~Order()
{
}

Order::Order(const UniqueID& id):
    _id(id)
{
}

Order::Order(const Order& rhs):
    _id(rhs._id),
    _participantID(rhs._participantID),
    _marketID(rhs._marketID),
    _status(rhs._status),
    _timestamp(rhs._timestamp),
    _quantity(rhs._quantity),
    _price(rhs._price),
    _direction(rhs._direction)
{}

Order& Order::operator=(const Order& rhs)
{
    _id            = rhs._id;
    _participantID = rhs._participantID;
    _marketID      = rhs._marketID;
    _status        = rhs._status;
    _timestamp     = rhs._timestamp;
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
