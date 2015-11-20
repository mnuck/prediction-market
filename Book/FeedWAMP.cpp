#include <autobahn/autobahn.hpp>

#include "FeedWAMP.h"

using namespace boost::asio;

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
    bool debug = true;
    _session = std::make_shared<autobahn::wamp_session>(_io, debug);

    ip::tcp::endpoint endpoint(
        ip::address::from_string("127.0.0.1"),
        8090);

    _transport = std::make_shared<autobahn::wamp_tcp_transport>(
        _io, endpoint, debug);

    _transport->attach(
        std::static_pointer_cast<autobahn::wamp_transport_handler>(_session));

    boost::future<void> connect_future;
    boost::future<void> start_future;
    boost::future<void> join_future;

    connect_future = _transport->connect().then([&](boost::future<void> connected) {
        try {
            connected.get();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            _io.stop();
            return;
        }

        if (debug)
            std::cerr << "transport connected" << std::endl;

        start_future = _session->start().then([&](boost::future<void> started) {
            try {
                started.get();
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                _io.stop();
                return;
            }

            if (debug)
                std::cerr << "session started" << std::endl;

            join_future = _session->join("realm1").then([&](boost::future<uint64_t> joined) {
                try {
                    if (debug)
                        std::cerr << "joined realm: " << joined.get() << std::endl;
                    boost::lock_guard<boost::mutex> lock(_cvm);
                    _ready = true;
                    _cvReady.notify_all();
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    _io.stop();
                    return;
                }
            });
        });
    });

    if (debug)
        std::cerr << "starting io service" << std::endl;
    _io.run();
    if (debug)
        std::cerr << "stopped io service" << std::endl;
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
    std::tuple<std::string> arguments(std::string("hello"));

    if (_ready)
        _session->publish("com.examples.subscriptions.topic1", arguments).get();
}
