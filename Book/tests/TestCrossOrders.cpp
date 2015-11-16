#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

using namespace Book;

SUITE(CrossOrders)
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
            UniqueID p3ID = b.GetUniqueID();
            m = Market(mID);
            
            p1 = Participant(p1ID);
            p1.SetBalance(10000);

            p2 = Participant(p2ID);
            p2.SetBalance(10000);
            
            p3 = Participant(p3ID);
            p3.SetBalance(10000);
            
            b.OpenMarket(m);
            b.OpenParticipant(p1);
            b.OpenParticipant(p2);
            b.OpenParticipant(p3);
        }
        
        Feed f;
        Book::Book b;
        Market m;
        Participant p1, p2, p3;
    };
    
    TEST_FIXTURE(BookFixture, CrossingOrdersExecute)
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

        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9950);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 100);
        CHECK(p2ms.inventory == -1);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, CrossingOrdersExecuteAtBuyerPrice)
    {
        UniqueID id1 = b.GetUniqueID();
        Order order1(id1);
        order1.SetParticipantID(p1.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(60);

        UniqueID id2 = b.GetUniqueID();
        Order order2(id2);
        order2.SetParticipantID(p2.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(50);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));

        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9940);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9960);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 100);
        CHECK(p2ms.inventory == -1);
        CHECK(p2ms.sellOrderQtySum == 0);
    }
    
    TEST_FIXTURE(BookFixture, LowerSellsExecuteFirst)
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
              .SetPrice(45);
              
        UniqueID id3 = b.GetUniqueID();
        Order order3(id3);
        order3.SetParticipantID(p3.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(40);

        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Order::Status::OPENED == b.OpenOrder(order3));
        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        const auto& p3r = b.GetParticipant(p3.GetID());
        const auto& p3ms = p3r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9900);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 100);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 1);
        
        CHECK(p3r.GetBalance() == 9950);
        CHECK(p3r.GetBuyEscrow() == 0);
        CHECK(p3r.GetCreateEscrow() == 100);
        CHECK(p3ms.inventory == -1);
        CHECK(p3ms.sellOrderQtySum == 0);
    }

    TEST_FIXTURE(BookFixture, HigherBuysExecuteFirst)
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
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(45);
              
        UniqueID id3 = b.GetUniqueID();
        Order order3(id3);
        order3.SetParticipantID(p3.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(40);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Order::Status::OPENED == b.OpenOrder(order3));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        const auto& p3r = b.GetParticipant(p3.GetID());
        const auto& p3ms = p3r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9955);
        CHECK(p2r.GetBuyEscrow() == 45);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
        
        CHECK(p3r.GetBalance() == 9950);
        CHECK(p3r.GetBuyEscrow() == 0);
        CHECK(p3r.GetCreateEscrow() == 100);
        CHECK(p3ms.inventory == -1);
        CHECK(p3ms.sellOrderQtySum == 0);
    }


    TEST_FIXTURE(BookFixture, HigherBuysExecuteFirstPlacementOrderIrrelevant)
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
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(45);
              
        UniqueID id3 = b.GetUniqueID();
        Order order3(id3);
        order3.SetParticipantID(p3.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(40);

        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order3));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        const auto& p3r = b.GetParticipant(p3.GetID());
        const auto& p3ms = p3r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9955);
        CHECK(p2r.GetBuyEscrow() == 45);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 0);
        CHECK(p2ms.sellOrderQtySum == 0);
        
        CHECK(p3r.GetBalance() == 9950);
        CHECK(p3r.GetBuyEscrow() == 0);
        CHECK(p3r.GetCreateEscrow() == 100);
        CHECK(p3ms.inventory == -1);
        CHECK(p3ms.sellOrderQtySum == 0);
    }


    TEST_FIXTURE(BookFixture, TimestampTiebreakerForIdenticalOrders)
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
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(1)
              .SetPrice(50);
              
        UniqueID id3 = b.GetUniqueID();
        Order order3(id3);
        order3.SetParticipantID(p3.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(1)
              .SetPrice(40);

        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order3));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        const auto& p3r = b.GetParticipant(p3.GetID());
        const auto& p3ms = p3r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 50);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 0);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9950);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 1);
        CHECK(p2ms.sellOrderQtySum == 0);
        
        CHECK(p3r.GetBalance() == 9950);
        CHECK(p3r.GetBuyEscrow() == 0);
        CHECK(p3r.GetCreateEscrow() == 100);
        CHECK(p3ms.inventory == -1);
        CHECK(p3ms.sellOrderQtySum == 0);
    }

    TEST_FIXTURE(BookFixture, BigSellConsumesMultipleBuys)
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
              .SetDirection(Order::Direction::BUY)
              .SetQuantity(3)
              .SetPrice(40);
              
        UniqueID id3 = b.GetUniqueID();
        Order order3(id3);
        order3.SetParticipantID(p3.GetID())
              .SetMarketID(m.GetID())
              .SetDirection(Order::Direction::SELL)
              .SetQuantity(5)
              .SetPrice(30);

        CHECK(Order::Status::OPENED == b.OpenOrder(order1));
        CHECK(Order::Status::OPENED == b.OpenOrder(order2));
        CHECK(Order::Status::OPENED == b.OpenOrder(order3));
        
        const auto& p1r = b.GetParticipant(p1.GetID());
        const auto& p1ms = p1r.GetMarketStats(m.GetID());

        const auto& p2r = b.GetParticipant(p2.GetID());
        const auto& p2ms = p2r.GetMarketStats(m.GetID());
        
        const auto& p3r = b.GetParticipant(p3.GetID());
        const auto& p3ms = p3r.GetMarketStats(m.GetID());

        CHECK(p1r.GetBalance() == 9950);
        CHECK(p1r.GetBuyEscrow() == 0);
        CHECK(p1r.GetCreateEscrow() == 0);
        CHECK(p1ms.inventory == 1);
        CHECK(p1ms.sellOrderQtySum == 0);

        CHECK(p2r.GetBalance() == 9880);
        CHECK(p2r.GetBuyEscrow() == 0);
        CHECK(p2r.GetCreateEscrow() == 0);
        CHECK(p2ms.inventory == 3);
        CHECK(p2ms.sellOrderQtySum == 0);
        
        CHECK(p3r.GetBalance() == 9670);
        CHECK(p3r.GetBuyEscrow() == 0);
        CHECK(p3r.GetCreateEscrow() == 500);
        CHECK(p3ms.inventory == -4);
        CHECK(p3ms.sellOrderQtySum == 1);
    }
}
