#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

SUITE(OrderOpenAndClose)
{
    class BookFixture
    {
    public:
        BookFixture(): 
            b(f)
        {
            UniqueID mID = b.GetUniqueID();
            UniqueID pID = b.GetUniqueID();
            m = Market(mID);
            
            p = Participant(pID);
            p.SetBalance(10000);
            
            b.OpenMarket(m);
            b.OpenParticipant(p);
        }
        Feed f;
        Book b;
        Market m;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, BuyOrdersMakeBuyEscrow)
    {
        UniqueID id = b.GetUniqueID();
        Order order(id);
        order.SetParticipantID(p.GetID())
             .SetMarketID(m.GetID())
             .SetDirection(Order::Direction::BUY)
             .SetQuantity(1)
             .SetPrice(50);
         
        CHECK(Order::Status::OPENED == b.OpenOrder(order));
        const auto& p2 = b.GetParticipant(p.GetID());
        const auto& p2ms = p2.GetMarketStats(m.GetID());
        
        CHECK(p2.GetBalance() == 9950);
        CHECK(p2.GetBuyEscrow() == 50);
        CHECK(p2.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, SellOrdersMakeCreateEscrow)
    {
        UniqueID id = b.GetUniqueID();
        Order order(id);
        order.SetParticipantID(p.GetID())
             .SetMarketID(m.GetID())
             .SetDirection(Order::Direction::SELL)
             .SetQuantity(1)
             .SetPrice(50);
         
        CHECK(Order::Status::OPENED == b.OpenOrder(order));
        const auto& p2 = b.GetParticipant(p.GetID());
        const auto& p2ms = p2.GetMarketStats(m.GetID());

        CHECK(p2.GetBalance() == 9900);
        CHECK(p2.GetBuyEscrow() == 0);
        CHECK(p2.GetCreateEscrow() == 100);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 1);
    }
    
    TEST_FIXTURE(BookFixture, ClosingBuyOrderReturnsEscrow)
    {
        UniqueID id = b.GetUniqueID();
        Order order(id);
        order.SetParticipantID(p.GetID())
             .SetMarketID(m.GetID())
             .SetDirection(Order::Direction::BUY)
             .SetQuantity(1)
             .SetPrice(50);
        
        CHECK(Order::Status::OPENED == b.OpenOrder(order));
        CHECK(Order::Status::CLOSED == b.CloseOrder(order.GetID()));
        
        const auto& p2 = b.GetParticipant(p.GetID());
        const auto& p2ms = p2.GetMarketStats(m.GetID());

        CHECK(p2.GetBalance() == 10000);
        CHECK(p2.GetBuyEscrow() == 0);
        CHECK(p2.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, ClosingSellOrderReturnsEscrow)
    {
        UniqueID id = b.GetUniqueID();
        Order order(id);
        order.SetParticipantID(p.GetID())
             .SetMarketID(m.GetID())
             .SetDirection(Order::Direction::SELL)
             .SetQuantity(1)
             .SetPrice(50);
     
        CHECK(Order::Status::OPENED == b.OpenOrder(order));
        CHECK(Order::Status::CLOSED == b.CloseOrder(order.GetID()));

        const auto& p2 = b.GetParticipant(p.GetID());
        const auto& p2ms = p2.GetMarketStats(m.GetID());

        CHECK(p2.GetBalance() == 10000);
        CHECK(p2.GetBuyEscrow() == 0);
        CHECK(p2.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }

}
