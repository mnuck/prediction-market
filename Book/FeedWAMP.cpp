#define BOOST_LOG_DYN_LINK 1

#include <map>

#include <boost/log/trivial.hpp>
#include <autobahn/autobahn.hpp>

#include "FeedWAMP.h"
#include "Logger.h"

using namespace boost::asio;
using boost::future;

FeedWAMP::FeedWAMP():
    _ready(false),
    _thread(&FeedWAMP::Connect, this)
{
    boost::unique_lock<boost::mutex> lock(_cvm);
    while (!_ready)
        _cvReady.wait(lock);
}

FeedWAMP::~FeedWAMP()
{
    _io.stop();
    if (_thread.joinable())
    {
        _thread.join();
    }
}

void FeedWAMP::Connect()
{
    ScopeLog scopelog(__FUNCTION__);

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

void FeedWAMP::Broadcast(const Book::Order& order)
{
    std::tuple<std::string> arguments(std::string("hello"));

    if (_ready)
        _session->publish("com.examples.subscriptions.topic1", arguments).get();
}

void FeedWAMP::Broadcast(const Book::Market& market)
{
    std::tuple<std::string> arguments(std::string("hello"));

    if (_ready)
        _session->publish("com.examples.subscriptions.topic1", arguments).get();
}

void FeedWAMP::Broadcast(const Book::Participant& participant)
{
    std::string topic = "com.examples.subscriptions.topic1";
    std::tuple<std::string> args(std::string("hello"));
    std::map<std::string, int> kwargs 
    {
        {"id", participant.GetID()},
    };

    if (_ready)
        _session->publish(topic ,args, kwargs).get();
}
