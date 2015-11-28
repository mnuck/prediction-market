#include "Logger.h"

template <typename T>
void WAMPAPI::Broadcast(std::string topic, T args)
{
    try
    {
        _endpoint.GetSession()->publish(topic, args).get();
    }
    catch (const std::exception& e)
    {
        LOG(error) << __FUNCTION__ 
                   << " caught exception: "
                   << e.what();
    } 
}

