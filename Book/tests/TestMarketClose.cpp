#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

SUITE(MarketClose)
{
    class BookFixture
    {
    public:
        BookFixture(): 
            b(f)
        {
            UniqueID mID  = b.GetUniqueID();
            UniqueID p1ID = b.GetUniqueID();
            UniqueID p2ID = b.GetUniqueID();
            m = Market(mID);
            m.SetDescription("This baby will fuss.");
            
            p1 = Participant(p1ID);
            p1.SetName("Alice");
            p1.SetBalance(10000);

            p2 = Participant(p2ID);
            p2.SetName("Bob");
            p2.SetBalance(10000);
            
            b.OpenMarket(m);
            b.OpenParticipant(p1);
            b.OpenParticipant(p2);
        }
        
        Feed f;
        Book b;
        Market m;
        Participant p1, p2;
    };
    
    TEST_FIXTURE(BookFixture, MarketCloseTrueClosesOrders)
    {
        UniqueID id1 = b.GetUniqueID();
        Order order1(id1);
        order1.SetParticipantID(p1.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(10);

        UniqueID id2 = b.GetUniqueID();
        Order order2(id2);
        order2.SetParticipantID(p2.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(90);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Market::Status::CLOSED == b.CloseMarket(m.GetID(), Market::Outcome::TRUE));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        CHECK(p1r.GetBalance() == 10000);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 0);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 10000);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, MarketCloseFalseClosesOrders)
    {
        UniqueID id1 = b.GetUniqueID();
        Order order1(id1);
        order1.SetParticipantID(p1.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(10);

        UniqueID id2 = b.GetUniqueID();
        Order order2(id2);
        order2.SetParticipantID(p2.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(90);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Market::Status::CLOSED == b.CloseMarket(m.GetID(), Market::Outcome::FALSE));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        CHECK(p1r.GetBalance() == 10000);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 0);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 10000);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, MarketCloseTrueRewardsPositiveInventory)
    {
        UniqueID id1 = b.GetUniqueID();
        Order order1(id1);
        order1.SetParticipantID(p1.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(50);

        UniqueID id2 = b.GetUniqueID();
        Order order2(id2);
        order2.SetParticipantID(p2.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(50);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Market::Status::CLOSED == b.CloseMarket(m.GetID(), Market::Outcome::TRUE));

        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());        
        
        CHECK(p1r.GetBalance() == 10050);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 0);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9950);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
    }

    TEST_FIXTURE(BookFixture, MarketCloseFalseRewardsNegativeInventory)
    {
        UniqueID id1 = b.GetUniqueID();
        Order order1(id1);
        order1.SetParticipantID(p1.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(50);

        UniqueID id2 = b.GetUniqueID();
        Order order2(id2);
        order2.SetParticipantID(p2.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(50);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Market::Status::CLOSED == b.CloseMarket(m.GetID(), Market::Outcome::FALSE));

        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());        
        
        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 0);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 10050);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);    }

    
}
