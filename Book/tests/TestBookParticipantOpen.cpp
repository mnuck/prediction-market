#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

using namespace Book;

SUITE(WAMPFeed)
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
        Book::Book b;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, OpenParticipant)
    {
        p.SetBalance(10000);
        CHECK(b.OpenParticipant(p) == Participant::Status::OPENED);
    }
}

