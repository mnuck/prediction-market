#define BOOST_LOG_DYN_LINK 1

#include <unittest++/UnitTest++.h>

#include "Logger.h"
#include "Preferences.h"

#include "Book.h"
#include "WAMPAPI.h"

int main(int argc, char **argv)
{
    ScopeLog scopelog(__FUNCTION__);
    
    prefs.ReadINI("/home/mnuck/prediction-market/Book.ini");
    SetLogLevel(prefs.Get("General.LogLevel", 0));
    
    if (argc > 1)
    {
        auto book = std::make_shared<Book::Book>();
        auto api = std::make_shared<WAMPAPI>();
        api->RegisterDelegate(book);
        book->RegisterBroadcastObserver(api);
        
        while (true)
            boost::this_thread::sleep_for(boost::chrono::seconds(10));
    }
    
    
    return UnitTest::RunAllTests();
}
