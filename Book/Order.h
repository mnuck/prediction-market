#ifndef ORDER_H
#define ORDER_H

#include "UniqueID.h"

class Order
{
public:
    static const unsigned int _value = 100;

    enum class Status
    {
        OPENED,
        CLOSED,
        FILLED,
        PARTIAL_FILLED,
        DUPLICATE,
        INVALID,
        INSUFFICIENT_BALANCE
    };
    
    enum class Direction
    {
        BUY,
        SELL
    };

    friend class Book;

    Order();
    Order(const UniqueID& id);
    Order(const Order& rhs);
    ~Order();
    
    Order& operator=(const Order& rhs);

    const UniqueID&     GetID() const;
    const UniqueID&     GetParticipantID() const;
    const UniqueID&     GetMarketID() const;    
    const Status&       GetStatus() const;
    const unsigned int& GetQuantity() const;
    const unsigned int& GetPrice() const;
    const Direction&    GetDirection() const;

    Order& SetParticipantID(const UniqueID& participantID);
    Order& SetMarketID(const UniqueID& marketID);
    Order& SetStatus(const Order::Status& status);
    Order& SetQuantity(const unsigned int& quantity);
    Order& SetPrice(const unsigned int& price);
    Order& SetDirection(const Order::Direction& direction);

private:
    UniqueID _id;
    UniqueID _participantID;
    UniqueID _marketID;
    Status   _status;

    unsigned int  _timestamp;
    unsigned int  _quantity;
    unsigned int  _price;
    Direction     _direction;
};

#endif // ORDER_H
