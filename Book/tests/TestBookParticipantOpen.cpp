#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

SUITE(OpenParticipant)
{
    class BookFixture
    {
    public:
        BookFixture(): 
            b(f)
        {
            UniqueID id = b.GetUniqueID();
            p = Participant(id);
        }
        Feed f;
        Book b;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, OpenParticipantNoName)
    {
        CHECK(b.OpenParticipant(p) == Participant::Status::INVALID_NAME);        
    }

    TEST_FIXTURE(BookFixture, OpenParticipant)
    {
        p.SetName("Alice");
        p.SetBalance(10000);
        CHECK(b.OpenParticipant(p) == Participant::Status::OPENED);
    }
    
    TEST_FIXTURE(BookFixture, GetParticipantReturnsSameParticipant)
    {
        p.SetName("Alice");
        p.SetBalance(10000);
        p.SetStatus(Participant::Status::OPENED);
        b.OpenParticipant(p);
        
        Participant p2 = b.GetParticipant(p.GetID());
        CHECK(p.GetID() == p2.GetID());
        CHECK(p.GetName() == p2.GetName());
        CHECK(p.GetStatus() == p2.GetStatus());
        CHECK(p.GetBalance() == p2.GetBalance());
        CHECK(p.GetBuyEscrow() == p2.GetBuyEscrow());
        CHECK(p.GetCreateEscrow() == p2.GetCreateEscrow());
    }
}

