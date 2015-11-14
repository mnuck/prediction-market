#ifndef BOOK_H
#define BOOK_H

#include <map>
#include <vector>

#include "Feed.h"
#include "Market.h"
#include "Order.h"
#include "Participant.h"
#include "UniqueID.h"

class Book
{
public:
    Book(Feed& feed);
    ~Book();

    UniqueID GetUniqueID();

    Order::Status OpenOrder(const Order& order);
    Order::Status CloseOrder(const UniqueID& orderID);

    std::vector<Market> GetMarkets() const;
    Market::Status OpenMarket(const Market& market);
    Market::Status CloseMarket(const UniqueID& marketID, const Market::Outcome& outcome);

    std::vector<Order> GetOrders(const Participant& participant) const;
    std::vector<Order> GetOrders(const Market& market) const;

    Participant::Status OpenParticipant(const Participant& participant);
    Participant::Status CloseParticipant(const UniqueID& participantID);
    const Participant&  GetParticipant(const UniqueID& participantID) const;

private:
    UniqueID GetTimestamp();
    void EraseOrder(const Order& order);
    void FullfillOrder(Order& order); // TODO
    void FullfillBuyOrder(Order& order); // TODO
    void FullfillSellOrder(Order& order); // TODO
    
    Feed&    _feed;
    UniqueID _uniqueID;
    UniqueID _timestamp;

    std::map<UniqueID, Market>      _markets;
    std::map<UniqueID, Order>       _orders;
    std::map<UniqueID, Participant> _participants;
    
    Participant _dummyParticipant;
};

#endif // BOOK_H
