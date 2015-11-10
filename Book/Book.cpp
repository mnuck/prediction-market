#include "Book.h"

Book::Book(Feed& feed):
    _feed(feed),
    _uniqueID(0)
{
    _dummyParticipant._id = 0;
    _dummyParticipant._status = Participant::Status::INVALID;
}

Book::~Book()
{
}

UniqueID Book::GetUniqueID()
{
    return ++_uniqueID;
}

Order::Status Book::OpenOrder(const Order& order)
{
    if (_orders.find(order._id) != _orders.end())
        return Order::Status::DUPLICATE;

    if (order._quantity == 0)
        return Order::Status::INVALID;

    if (_participants.find(order._participantID) == _participants.end())
        return Order::Status::INVALID;

    if (_markets.find(order._marketID) == _markets.end())
        return Order::Status::INVALID;

    Participant& p = _participants[order._participantID];
    Participant::MarketStats& marketStats = p._marketStats.at(order._marketID);

    if (order._direction == Order::Direction::BUY)
    {
        unsigned int buyEscrow = order._quantity * order._price;
        if (p._balance < buyEscrow)
            return Order::Status::INSUFFICIENT_BALANCE;

        p._balance   -= buyEscrow;
        p._buyEscrow += buyEscrow;
    }
    else if (order._direction == Order::Direction::SELL) // don't judge
    {
        int uncoveredSellQty = marketStats.inventory - (marketStats.sellOrderQtySum + order._quantity);
        if (uncoveredSellQty < 0)
        {
            unsigned int sellEscrow = order._quantity * order._value;
            if (p._balance < sellEscrow)
                return Order::Status::INSUFFICIENT_BALANCE;

            p._balance    -= sellEscrow;
            p._sellEscrow += sellEscrow;
            marketStats.sellOrderQtySum += order._quantity;
        }
    }

    _orders[order._id] = order;
    _orders[order._id]._status = Order::Status::OPENED;    
    _markets[order._marketID]._orders.insert(order._id);    

    p._orders.insert(order._id);

    _feed.Broadcast(_orders[order._id]);
    FullfillOrder(_orders[order._id]);
    return Order::Status::OPENED;
}

Order::Status Book::CloseOrder(const Order& a_order)
{
    auto it = _orders.find(a_order._id);
    if (it == _orders.end())
        return Order::Status::INVALID;
    
    Order& order = it->second;
    
    if (_participants.find(order._participantID) == _participants.end())
        return Order::Status::INVALID;

    if (_markets.find(order._marketID) == _markets.end())
        return Order::Status::INVALID;

    Participant& p = _participants[order._participantID];
    Participant::MarketStats& marketStats = p._marketStats.at(order._marketID);
    if (order._direction == Order::Direction::BUY)
    {
        unsigned int buyEscrow = order._quantity * order._price;
        p._balance   += buyEscrow;
        p._buyEscrow -= buyEscrow;
    }
    else if (order._direction == Order::Direction::SELL) // don't judge
    {
        unsigned int sellEscrow = order._quantity * order._value;
        if (sellEscrow > p._sellEscrow)
        {
            p._balance   += p._sellEscrow;
            p._sellEscrow = 0;
        }
        else
        {
            p._balance    += sellEscrow;
            p._sellEscrow -= sellEscrow;
        }
        marketStats.sellOrderQtySum -= order._quantity;        
    }

    Order result(it->second);
    _orders.erase(order._id);
    _participants[order._participantID]._orders.erase(order._id);
    _markets[order._marketID]._orders.erase(order._id);
    result._status = Order::Status::CLOSED;
    
    _feed.Broadcast(result);    
    return Order::Status::CLOSED;
}

void Book::FullfillOrder(const Order& order)
{
    // TODO potentially this new order will trigger sales
}


std::vector<Market> Book::GetMarkets() const
{
    std::vector<Market> result;
    for (auto& m : _markets)
    {
        result.push_back(m.second);
    }
    return result;
}

Market::Status Book::OpenMarket(const Market& market)
{
    UniqueID id = market._id;
    if (_markets.find(id) != _markets.end())
        return Market::Status::DUPLICATE;
    
    if (market._description == "")
        return Market::Status::INVALID;
        
    _markets[id] = market;
    _markets[id]._outcome = Market::Outcome::UNKNOWN;
    _markets[id]._status = Market::Status::OPENED;
    _feed.Broadcast(_markets.at(id));
    return Market::Status::OPENED;
}

Market::Status Book::CloseMarket(const Market& market)
{
    UniqueID id = market.GetID();
    if (_markets.find(id) == _markets.end())
        return Market::Status::INVALID;
        
    if (_markets[id].GetStatus() != Market::Status::OPENED)
        return Market::Status::INVALID;

    if (market.GetOutcome() == Market::Outcome::UNKNOWN)
        return Market::Status::INVALID;

    for (const auto& oid : _orders)
    {
        Order order(oid.first);
        CloseOrder(order);        
    }
    
    Market result(_markets.find(id)->second);
    _markets.erase(id);
    result.SetStatus(Market::Status::CLOSED)
          .SetOutcome(market.GetOutcome());
    _feed.Broadcast(result);
    return Market::Status::CLOSED;    
}

std::vector<Order> Book::GetOrders(const Participant& participant) const
{
    std::vector<Order> result;
    auto it = _participants.find(participant._id);
    if (it == _participants.end())
        return result;
        
    for (const auto& orderID : it->second._orders)
    {
        result.push_back(_orders.at(orderID));
    }
    return result;
}

std::vector<Order> Book::GetOrders(const Market& market) const
{
    std::vector<Order> result;
    auto it = _markets.find(market._id);
    if (it == _markets.end())
        return result;
        
    for (const auto& orderID : it->second._orders)
    {
        result.push_back(_orders.at(orderID));
    }
    return result;
}

Participant::Status Book::OpenParticipant(const Participant& participant)
{
    UniqueID id = participant._id;
    
    if (_participants.find(id) != _participants.end())
        return Participant::Status::DUPLICATE;
    
    if (participant._buyEscrow != 0)
        return Participant::Status::INVALID;
        
    if (participant._name == "")
        return Participant::Status::INVALID;
    
    _participants[id] = participant;
    _participants[id]._status = Participant::Status::OPENED;
    _feed.Broadcast(_participants[id]);
    return Participant::Status::OPENED;
}

Participant::Status Book::CloseParticipant(const Participant& participant)
{
    UniqueID id = participant.GetID();
    if (_participants.find(id) == _participants.end())
        return Participant::Status::INVALID;
        
    if (participant._buyEscrow != 0)
        return Participant::Status::CAN_NOT_CLOSE;

    if (participant._sellEscrow != 0)
        return Participant::Status::CAN_NOT_CLOSE;

    if (participant.GetStatus() != Participant::Status::OPENED)
        return Participant::Status::CAN_NOT_CLOSE;
        
    if (!participant._marketStats.empty())
        return Participant::Status::CAN_NOT_CLOSE;

    for (const auto& oid : _participants.find(id)->second._orders)
    {
        Order order(oid);
        CloseOrder(order);        
    }
    
    Participant result(_participants.find(id)->second);
    _participants.erase(id);
    result.SetStatus(Participant::Status::CLOSED);
    _feed.Broadcast(result);
    return Participant::Status::CLOSED;    
}

const Participant& Book::GetParticipant(const UniqueID& participantID) const
{
    auto it = _participants.find(participantID);
    if (it == _participants.end())
        return _dummyParticipant;
    else
        return it->second;
}
