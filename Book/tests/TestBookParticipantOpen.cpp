#include <unittest++/UnitTest++.h>

#include "FeedStdOut.h"
#include "Book.h"

using namespace Book;

SUITE(ParticipantOpen)
{
    class BookFixture
    {
    public:
        BookFixture()
        {
            UniqueID id = b.GetUniqueID();
            p = Participant(id);
        }
        Book::Book b;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, OpenParticipant)
    {
        p.SetBalance(10000);
        CHECK(b.OpenParticipant(p) == Participant::Response::OPENED);
    }
}

