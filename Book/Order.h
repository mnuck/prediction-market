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
        PARTIAL_FILLED,
        FILLED,
        DUPLICATE,
        NO_SUCH_ORDER,
        UNINITIALIZED,
        INVALID_QUANTITY,
        INVALID_MARKET,
        INVALID_PARTICIPANT,
        INSUFFICIENT_BALANCE
    };
    
    enum class Direction
    {
        BUY,
        SELL
    };

    class CompareSells
    {
    public:
        bool operator()(const Order& lhs, const Order& rhs);
    };

    class CompareBuys
    {
    public:
        bool operator()(const Order& lhs, const Order& rhs);
    };

    friend class Book;

    Order();
    Order(const UniqueID& id);
    Order(const Order& rhs);
    ~Order();
    
    Order& operator=(const Order& rhs);

    const UniqueID&         GetID() const;
    const UniqueID&         GetParticipantID() const;
    const UniqueID&         GetMarketID() const;    
    const Order::Status&    GetStatus() const;
    const unsigned int&     GetQuantity() const;
    const unsigned int&     GetPrice() const;
    const Order::Direction& GetDirection() const;

    Order& SetParticipantID(const UniqueID& participantID);
    Order& SetMarketID(const UniqueID& marketID);
    Order& SetStatus(const Order::Status& status);
    Order& SetQuantity(const unsigned int& quantity);
    Order& SetPrice(const unsigned int& price);
    Order& SetDirection(const Order::Direction& direction);
    
private:
    UniqueID      _id;
    UniqueID      _participantID;
    UniqueID      _marketID;
    UniqueID      _timestamp;
    Order::Status _status;

    unsigned int     _quantity;
    unsigned int     _price;
    Order::Direction _direction;
};

#endif // ORDER_H
