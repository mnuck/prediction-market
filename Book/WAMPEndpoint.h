#ifndef WAMPENDPOINT_H
#define WAMPENDPOINT_H

#include <autobahn/autobahn.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

class WAMPEndpoint
{
public:
    WAMPEndpoint();
    ~WAMPEndpoint();

    std::shared_ptr<autobahn::wamp_session> GetSession();
    
protected:
    void WAMPConnect();

    const std::string _realm;
    const std::string _ipAddr;
    const uint16_t    _ipPort;

    bool _ready;
    boost::thread _thread;
    boost::asio::io_service _io;
    std::shared_ptr<autobahn::wamp_session> _session;
    std::shared_ptr<autobahn::wamp_tcp_transport> _transport;
    
    boost::condition_variable _cvReady;
    boost::mutex _cvm;
};

#endif // WAMPENDPOINT_H
