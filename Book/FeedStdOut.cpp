#include <iostream>
#include <string>

#include "FeedStdOut.h"

using std::cout;
using std::endl;
using std::string;

FeedStdOut::FeedStdOut()
{
}

FeedStdOut::~FeedStdOut()
{
}

void FeedStdOut::Broadcast(const Order& order)
{
    string sStatus;
    switch (order.GetStatus())
    {
    case Order::Status::CLOSED:
        sStatus = "CLOSED";
        break;
    case Order::Status::DUPLICATE:
        sStatus = "DUPLICATE";
        break;
    case Order::Status::FILLED:
        sStatus = "FILLED";
        break;
    case Order::Status::UNINITIALIZED:
        sStatus = "UNINITIALIZED";
        break;
    case Order::Status::OPENED:
        sStatus = "OPENED";
        break;
    case Order::Status::PARTIAL_FILLED:
        sStatus = "PARTIAL_FILLED";
        break;
    default:
        sStatus = "BROKEN";
        break;
    }

    cout << "order #" << order.GetID() << "\n"
         << "market " << order.GetMarketID() << "\n"
         << "owner  " << order.GetParticipantID() << "\n"
         << (order.GetDirection() == Order::Direction::SELL ? "SELL " : "BUY ")
         << order.GetQuantity() << " at "
         << order.GetPrice() << "\n"
         << "Status: " << sStatus << endl;
    
}

void FeedStdOut::Broadcast(const Market& market)
{
    string outcome;
    string status;
    
    switch (market.GetOutcome())
    {
    case Market::Outcome::TRUE:
        outcome = "TRUE";
        break;
    case Market::Outcome::FALSE:
        outcome = "FALSE";
        break;
    case Market::Outcome::UNKNOWN:
        outcome = "UNKNOWN";
        break;
    default:
        outcome = "BROKEN";
        break;
    }
    
    switch (market.GetStatus())
    {
    case Market::Status::OPENED:
        status = "OPENED";
        break;
    case Market::Status::CLOSED:
        status = "CLOSED";
        break;
    case Market::Status::DUPLICATE:
        status = "DUPLICATE";
        break;
    case Market::Status::INVALID_DESCRIPTION:
        status = "INVALID_DESCRIPTION";
        break;
    default:
        status = "BROKEN";
        break;
    }
    
    cout << "market " << market.GetID() << "\n"
     << "market " << market.GetDescription() << "\n"
     << "Status:  " << status << "\n"
     << "Outcome: " << outcome << endl;
}

void FeedStdOut::Broadcast(const Participant& participant)
{
    cout << "participant " << participant.GetID() << "\n"
     << "Name: " << participant.GetName() << "\n"
     << "Balance: " << participant.GetBalance() << "\n"
     << "Buy Escrow: " << participant.GetBuyEscrow() << "\n"
     << "Create Escrow: " << participant.GetCreateEscrow() << endl;
}
