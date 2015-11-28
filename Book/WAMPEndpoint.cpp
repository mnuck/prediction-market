#include "Logger.h"
#include "Preferences.h"
#include "WAMPEndpoint.h"

using namespace boost::asio;
using boost::future;


WAMPEndpoint::WAMPEndpoint():
    _realm(prefs.Get("WAMP.Realm", std::string("default"))),
    _ipAddr(prefs.Get("WAMP.IPAddress",std::string("127.0.0.1"))),
    _ipPort(prefs.Get("WAMP.IPPort", 8090)),
    _ready(false),
    _thread(&WAMPEndpoint::WAMPConnect, this)
{
    boost::unique_lock<boost::mutex> lock(_cvm);
    while (!_ready)
        _cvReady.wait(lock);
}

WAMPEndpoint::~WAMPEndpoint()
{
    _io.stop();
    if (_thread.joinable())
    {
        _thread.join();
    }
}

std::shared_ptr<autobahn::wamp_session> WAMPEndpoint::GetSession()
{
    return _session;
}

void WAMPEndpoint::WAMPConnect()
{
    ScopeLog scopelog("WAMPEndpoint::Connect");
    
    bool debug = false;
    _session = std::make_shared<autobahn::wamp_session>(_io, debug);

    ip::tcp::endpoint endpoint(ip::address::from_string(_ipAddr), _ipPort);

    _transport = std::make_shared<autobahn::wamp_tcp_transport>(
        _io, endpoint, debug);

    _transport->attach(
        std::static_pointer_cast<autobahn::wamp_transport_handler>(_session));

    future<void> connect_future;
    future<void> start_future;
    future<void> join_future;

    try
    {
        connect_future = _transport->connect().then(
            [&](future<void> connected) {
                connected.get();
            
                LOG(trace) << "transport connected";
            
                start_future = _session->start().then(
                    [&](future<void> started) {
                        started.get();
                    
                        LOG(trace) << "session started";
                    
                        join_future = _session->join("realm1").then(
                            [&](future<uint64_t> joined) {
                            
                                LOG(trace) << "joined realm: "
                                           << joined.get();

                                boost::lock_guard<boost::mutex> lock(_cvm);
                                _ready = true;
                                _cvReady.notify_all();
                            });
                    });
            });
    }
    catch (const std::exception& e)
    {
        LOG(error) << __FUNCTION__
                   << " caught exception: "
                   << e.what();
        _io.stop();
        return;
    }

    LOG(trace) << "starting io service";
    _io.run();
    LOG(trace) << "stopped io service";
}
