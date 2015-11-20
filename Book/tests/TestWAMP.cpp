#include <unittest++/UnitTest++.h>

#include "FeedWAMP.h"
#include "FeedStdOut.h"
#include "Book.h"

using namespace Book;

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
        FeedWAMP f;
        Book::Book b;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, OpenParticipant)
    {
        p.SetBalance(10000);
        CHECK(b.OpenParticipant(p) == Participant::Status::OPENED);
    }
}

