#define BOOST_LOG_DYN_LINK 1

#include <unittest++/UnitTest++.h>

#include "Logger.h"

int main(int argc, char **argv)
{
    ScopeLog scopelog(__FUNCTION__);
    SetLogLevel(prefs.Get("General.LogLevel", 3));
    
    
    LOG(trace) << "no see me";
    
        
    return UnitTest::RunAllTests();
}
