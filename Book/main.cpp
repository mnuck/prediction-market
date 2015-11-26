#define BOOST_LOG_DYN_LINK 1

#include <unittest++/UnitTest++.h>

#include "Logger.h"
#include "Preferences.h"

int main(int argc, char **argv)
{
    ScopeLog scopelog(__FUNCTION__);
    
    prefs.ReadINI("Book.ini");
    SetLogLevel(prefs.Get("General.LogLevel", 3));
    
    
    LOG(trace) << "no see me";
    
        
    return UnitTest::RunAllTests();
}
