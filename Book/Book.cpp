#include "Book.h"


const Participant Book::_dummyParticipant;

Book::Book(Feed& feed):
    _feed(feed),
    _uniqueID(0),
    _timestamp(0)
{
}

Book::~Book()
{
}

UniqueID Book::GetUniqueID()
{
    return ++_uniqueID;
}

UniqueID Book::GetTimestamp()
{
    return ++_timestamp;
}

Order::Status Book::OpenOrder(const Order& order)
{
    if (_orders.find(order._id) != _orders.end())
        return Order::Status::DUPLICATE;

    if (order._quantity == 0)
        return Order::Status::INVALID_QUANTITY;

    auto partIter = _participants.find(order._participantID);
    if (partIter == _participants.end())
        return Order::Status::INVALID_PARTICIPANT;

    if (_markets.find(order._marketID) == _markets.end())
        return Order::Status::INVALID_MARKET;

    auto& participant = partIter->second;
    auto& marketStats = participant._marketStats[order._marketID];

    if (order._direction == Order::Direction::BUY)
    {
        unsigned int buyEscrow = order._quantity * order._price;
        if (participant._balance < buyEscrow)
            return Order::Status::INSUFFICIENT_BALANCE;

        participant._balance   -= buyEscrow;
        participant._buyEscrow += buyEscrow;
    }
    else if (order._direction == Order::Direction::SELL) // don't judge
    {
        int uncoveredSellQty = marketStats.inventory - (marketStats.sellOrderQtySum + order._quantity);
        if (uncoveredSellQty < 0)
        {
            unsigned int sellEscrow = order._quantity * order._value;
            if (participant._balance < sellEscrow)
                return Order::Status::INSUFFICIENT_BALANCE;

            participant._balance    -= sellEscrow;
            participant._createEscrow += sellEscrow;
        }
        marketStats.sellOrderQtySum += order._quantity;
    }

    auto iterAndBool = _orders.insert(std::pair<UniqueID, Order>(order._id, order));
    Order& newOrder = iterAndBool.first->second;
    newOrder._status = Order::Status::OPENED;
    newOrder._timestamp = GetTimestamp();
    _markets.at(order._marketID)._orders.insert(order._id);
    participant._orders.insert(order._id);

    _feed.Broadcast(newOrder);
    FullfillOrder(newOrder);
    return Order::Status::OPENED;
}

Order::Status Book::CloseOrder(const UniqueID& oID)
{
    auto oIter = _orders.find(oID);
    if (oIter == _orders.end())
        return Order::Status::NO_SUCH_ORDER;
    
    auto& order = oIter->second;
    auto& participant = _participants.at(order._participantID);
    auto& marketStats = participant._marketStats.at(order._marketID);

    if (order._direction == Order::Direction::BUY)
    {
        unsigned int buyEscrow = order._quantity * order._price;
        participant._balance   += buyEscrow;
        participant._buyEscrow -= buyEscrow;
    }
    else if (order._direction == Order::Direction::SELL) // don't judge
    {
        int currentUncoveredSellQty = std::max(0, marketStats.sellOrderQtySum - marketStats.inventory);        
        marketStats.sellOrderQtySum -= order._quantity;
        int newUncoveredSellQty     = std::max(0, marketStats.sellOrderQtySum - marketStats.inventory);
        
        int deltaQty = newUncoveredSellQty - currentUncoveredSellQty;
        if (deltaQty < 0)
        {
            participant._balance      -= deltaQty * order._value;
            participant._createEscrow += deltaQty * order._value;
        }
    }

    Order result(order);
    _orders.erase(oIter);
    _participants.at(result._participantID)._orders.erase(result._id);
    _markets.at(result._marketID)._orders.erase(result._id);
    result._status = Order::Status::CLOSED;
    
    _feed.Broadcast(result);
    return Order::Status::CLOSED;
}

void Book::FullfillOrder(Order& order)
{
    Market& market = _markets.at(order._marketID);
    auto& sellOrders = market._sellOrders;
    auto& buyOrders  = market._buyOrders;

    if (order._direction == Order::Direction::BUY)
    {
        if (sellOrders.empty())
        {
            buyOrders.push(order);
            return;
        }
        while (!sellOrders.empty())
        {
            Order existingOrder = sellOrders.top();
            Order& buyOrder = order;
            Order& sellOrder = existingOrder;

            if (order._price < existingOrder._price)
            { 
                buyOrders.push(order);
                return;
            }

            sellOrders.pop();
            if (CrossOrders(order, existingOrder, buyOrder, sellOrder, market))
                return;
        }
    }
    else if (order._direction == Order::Direction::SELL) // don't judge
    {
        if (buyOrders.empty())
        {
            sellOrders.push(order);
            return;
        }
        while (!buyOrders.empty())
        {
            Order existingOrder = buyOrders.top();
            Order& buyOrder = existingOrder;
            Order& sellOrder = order;        
            
            if (order._price > existingOrder._price)
            {
                sellOrders.push(order);
                return;
            }
            
            buyOrders.pop();
            if (CrossOrders(order, existingOrder, buyOrder, sellOrder, market))
                return;   
        }
    }
}



bool Book::CrossOrders(
    Order& newOrder, Order& existingOrder,
    Order& buyOrder, Order& sellOrder,
    Market& market)
{
    bool done = false;
    auto& sellOrders = market._sellOrders;
    auto& buyOrders  = market._buyOrders;
    Participant& buyer  = _participants.at(buyOrder._participantID);
    Participant& seller = _participants.at(sellOrder._participantID); 

    Participant::MarketStats& buyerMarketStats   = buyer._marketStats[market._id];
    Participant::MarketStats& sellerMarketStats  = seller._marketStats[market._id];

    if (existingOrder._quantity < newOrder._quantity)
    {
        buyer._buyEscrow -= existingOrder._quantity * buyOrder._price;
        seller._balance  += existingOrder._quantity * buyOrder._price;

        buyerMarketStats.inventory        += existingOrder._quantity;
        sellerMarketStats.inventory       -= existingOrder._quantity;
        sellerMarketStats.sellOrderQtySum -= existingOrder._quantity;
        
        existingOrder._status = Order::Status::FILLED;

        newOrder._status = Order::Status::PARTIAL_FILLED;
        newOrder._quantity -= existingOrder._quantity;

        _feed.Broadcast(newOrder);
        _feed.Broadcast(existingOrder);
        EraseOrder(existingOrder);
    }
    else
    {
        buyer._buyEscrow -= newOrder._quantity * buyOrder._price;
        seller._balance  += newOrder._quantity * buyOrder._price;

        buyerMarketStats.inventory        += newOrder._quantity;
        sellerMarketStats.inventory       -= newOrder._quantity;
        sellerMarketStats.sellOrderQtySum -= newOrder._quantity;

        if (existingOrder._quantity > newOrder._quantity)
        {
            existingOrder._status = Order::Status::PARTIAL_FILLED;
            existingOrder._quantity -= newOrder._quantity;
            if (existingOrder._direction == Order::Direction::SELL)
                sellOrders.push(existingOrder);
            else
                buyOrders.push(existingOrder);
        }
        else // quantities are equal
        {
            existingOrder._status = Order::Status::FILLED;
            EraseOrder(existingOrder);
        }

        newOrder._status = Order::Status::FILLED;
        _feed.Broadcast(newOrder);
        _feed.Broadcast(existingOrder);
        EraseOrder(newOrder);
        done = true;
    }
    return done;    
}


void Book::EraseOrder(const Order& order)
{
    _orders.erase(order._id);
    _participants
        .at(order._participantID)
        ._orders
        .erase(order._id);
    _markets
        .at(order._marketID)
        ._orders
        .erase(order._id);
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
    UniqueID marketID = market._id;
    if (_markets.find(marketID) != _markets.end())
        return Market::Status::DUPLICATE;
    
    if (market._description == "")
        return Market::Status::INVALID_DESCRIPTION;

    auto iterAndBool = _markets.insert(std::pair<UniqueID, Market>(marketID, market));
    Market& newMarket = iterAndBool.first->second;
    newMarket._outcome = Market::Outcome::UNKNOWN;
    newMarket._status = Market::Status::OPENED;

    _feed.Broadcast(newMarket);
    return Market::Status::OPENED;
}

Market::Status Book::CloseMarket(const UniqueID& marketID, const Market::Outcome& outcome)
{
    auto marketIter = _markets.find(marketID);
    if (marketIter == _markets.end())
        return Market::Status::NO_SUCH_MARKET;

    if (outcome == Market::Outcome::UNKNOWN)
        return Market::Status::INVALID_OUTCOME;

    for (const auto& oid : _orders)
    {
        CloseOrder(oid.first);        
    }
    
    for (auto& pPair: _participants)
    {
        Participant& participant = pPair.second;
        auto msIter = participant._marketStats.find(marketID);
        if (msIter == participant._marketStats.end())
            continue;
        
        if (msIter->second.inventory < 0)
        {
            // negative inventory, += subtracts, -= adds
            participant._createEscrow += msIter->second.inventory * Order::_value;
            if (outcome == Market::Outcome::FALSE)
            {
                participant._balance -= msIter->second.inventory * Order::_value;
            }
        }
        else if (msIter->second.inventory > 0)
        {
            if (outcome == Market::Outcome::TRUE)
            {
                participant._balance += msIter->second.inventory * Order::_value;
            }
        }
        
        participant._marketStats.erase(msIter);
    }
    
    Market result(marketIter->second);
    _markets.erase(marketIter);
    result._status = Market::Status::CLOSED;
    result._outcome = outcome;
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
    UniqueID participantID = participant._id;
    
    if (_participants.find(participantID) != _participants.end())
        return Participant::Status::DUPLICATE;
    
    if (participant._buyEscrow != 0)
        return Participant::Status::INVALID_ESCROW;
        
    if (participant._name == "")
        return Participant::Status::INVALID_NAME;
    
    auto iterAndBool = _participants.insert(std::pair<UniqueID, Participant>(participantID, participant));
    Participant& newParticipant = iterAndBool.first->second;
    
    newParticipant._status = Participant::Status::OPENED;
    _feed.Broadcast(newParticipant);
    return Participant::Status::OPENED;
}

Participant::Status Book::CloseParticipant(const UniqueID& participantID)
{
    auto participantIter = _participants.find(participantID);
    if (participantIter == _participants.end())
        return Participant::Status::NO_SUCH_PARTICIPANT;
        
    Participant& participant = participantIter->second;

    if (participant._buyEscrow != 0)
        return Participant::Status::CAN_NOT_CLOSE;

    if (participant._createEscrow != 0)
        return Participant::Status::CAN_NOT_CLOSE;

    if (!participant._marketStats.empty())
        return Participant::Status::CAN_NOT_CLOSE;

    for (const auto& oid : participantIter->second._orders)
    {
        CloseOrder(oid);        
    }
    
    Participant result(participant);
    _participants.erase(participantIter);
    result._status = Participant::Status::CLOSED;

    _feed.Broadcast(result);
    return Participant::Status::CLOSED;    
}

const Participant& Book::GetParticipant(const UniqueID& participantID) const
{
    auto participantIter = _participants.find(participantID);
    if (participantIter == _participants.end())
        return _dummyParticipant;
    else
        return participantIter->second;
}
