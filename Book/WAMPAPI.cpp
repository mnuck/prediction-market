#define BOOST_LOG_DYN_LINK 1

#include "WAMPAPI.h"

#include <boost/log/trivial.hpp>

using namespace boost::asio;
using boost::future;

WAMPAPI::WAMPAPI():
    _ready(false),
    _thread(&WAMPAPI::Connect, this)
{
    boost::unique_lock<boost::mutex> lock(_cvm);
    while (!_ready)
        _cvReady.wait(lock);
}

WAMPAPI::~WAMPAPI()
{
    _io.stop();
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void WAMPAPI::Connect()
{
    bool debug = false;
    _session = std::make_shared<autobahn::wamp_session>(_io, debug);

    ip::tcp::endpoint endpoint(
        ip::address::from_string("127.0.0.1"),
        8090);

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
            
                BOOST_LOG_TRIVIAL(trace) << "transport connected";
            
                start_future = _session->start().then(
                    [&](future<void> started) {
                        started.get();
                    
                        BOOST_LOG_TRIVIAL(trace) << "session started";
                    
                        join_future = _session->join("realm1").then(
                            [&](future<uint64_t> joined) {
                            
                                BOOST_LOG_TRIVIAL(trace) << "joined realm: " 
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
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ 
                                 << " caught exception: "
                                 << e.what();
        _io.stop();
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "starting io service";
    _io.run();
    BOOST_LOG_TRIVIAL(trace) << "stopped io service";
}


void WAMPAPI::OnBroadcast(const Book::Order& order)
{
}

void WAMPAPI::OnBroadcast(const Book::Market& market)
{
}

void WAMPAPI::OnBroadcast(const Book::Participant& participant)
{
}

