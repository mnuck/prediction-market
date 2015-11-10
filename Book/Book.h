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

    Order::Status OpenOrder(const Order& order); // TODO
    Order::Status CloseOrder(const Order& order); // TODO
    void FullfillOrder(const Order& order); // TODO

    std::vector<Market> GetMarkets() const;
    Market::Status OpenMarket(const Market& market);
    Market::Status CloseMarket(const Market& outcome);

    std::vector<Order> GetOrders(const Participant& participant) const;
    std::vector<Order> GetOrders(const Market& market) const;

    Participant::Status OpenParticipant(const Participant& participant);
    Participant::Status CloseParticipant(const Participant& participant);
    const Participant& GetParticipant(const UniqueID& participantID) const;

private:
    Feed&    _feed;
    UniqueID _uniqueID;

    std::map<UniqueID, Market>      _markets;
    std::map<UniqueID, Order>       _orders;
    std::map<UniqueID, Participant> _participants;
    
    Participant _dummyParticipant;
};

#endif // BOOK_H
