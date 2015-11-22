#define BOOST_LOG_DYN_LINK 1

#include <unittest++/UnitTest++.h>

#include "Logger.h"

int main(int argc, char **argv)
{
    ScopeLog scopelog(__FUNCTION__);
    
    LOG(warning) << "a thing happened";
    
    return UnitTest::RunAllTests();
}
