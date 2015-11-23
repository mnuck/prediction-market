#include <memory>

#include <unittest++/UnitTest++.h>

#include "FeedWAMP.h"
#include "FeedStdOut.h"
#include "Book.h"

using namespace Book;

SUITE(WAMP)
{
    class BookFixture
    {
    public:
        BookFixture()
        {
            UniqueID id = b.GetUniqueID();
            p = Participant(id);
            
            f = std::make_shared<FeedWAMP>();
            b.RegisterBroadcastObserver(f);
        }
        
        std::shared_ptr<FeedWAMP> f;
        Book::Book b;
        Participant p;
    };
    
    TEST_FIXTURE(BookFixture, WAMP)
    {
        p.SetBalance(10000);
        CHECK(b.OpenParticipant(p) == Participant::Status::OPENED);
    }
}

