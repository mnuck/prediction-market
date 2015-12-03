#include <memory>

//#include <boost/thread.hpp>
#include <unittest++/UnitTest++.h>

#include "WAMPAPI.h"
#include "Book.h"

using namespace Book;

SUITE(WAMP_API)
{
    class WAMPFixture
    {
    public:
        WAMPFixture()
        {
            book = std::make_shared<Book::Book>();
            api = std::make_shared<WAMPAPI>();
            api->RegisterDelegate(book);
            book->RegisterBroadcastObserver(api);
            UniqueID id = book->GetUniqueID();
            p = Participant(id);
        }
        
        std::shared_ptr<WAMPAPI> api;
        std::shared_ptr<Book::Book> book;
        Participant p;
    };
    
    TEST_FIXTURE(WAMPFixture, WAMPLoads)
    {
        p.SetBalance(10000);
        CHECK(book->OpenParticipant(p) == Participant::Response::OPENED);
    }
}
