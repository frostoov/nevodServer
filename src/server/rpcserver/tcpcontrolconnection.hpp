#ifndef TCPCONTROLCONNECTION_HPP
#define TCPCONTROLCONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "dispatcher.hpp"
#include "jsonwriter.hpp"
#include "jsonreader.hpp"

class TcpControlConnection
    : public std::enable_shared_from_this<TcpControlConnection> {
public:
    using TcpControlConnectionPtr = std::shared_ptr<TcpControlConnection>;
    using DispatcherPtr = std::shared_ptr<Dispatcher>;

    TcpControlConnection(boost::asio::io_service& service,
                         Dispatcher& dispatcher);
    ~TcpControlConnection();

    static TcpControlConnectionPtr create(boost::asio::io_service& service,
                                   Dispatcher& dispatcher);
    boost::asio::ip::tcp::socket& getSocket();
    void start();
    bool isConnected() const;

protected:
    void handleWrite(const boost::system::error_code& error, size_t);
    void handleRead(const boost::system::error_code& error);
    std::string answerToRequest(const std::string& message_);

private:
    Dispatcher& dispatcher_;
    std::unique_ptr<JsonWriter> writer_;

    boost::asio::ip::tcp::socket socket_;
    std::string message_;
    std::vector<char> buf_;
    boost::asio::streambuf response_;
    bool isConnected_;
};

#endif  // TCPCONTROLCONNECTION_HPP
