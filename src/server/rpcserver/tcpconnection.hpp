#ifndef TCPCONNECTION_HPP
#define TCPCONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "dispatcher.hpp"
#include "jsonwriter.hpp"
#include "jsonreader.hpp"

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
public:
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using DispatcherPtr = std::shared_ptr<Dispatcher>;

    TcpConnection(boost::asio::io_service& service, Dispatcher& dispatcher);
    ~TcpConnection();

    static TcpConnectionPtr create(boost::asio::io_service& service,
                                   Dispatcher& dispatcher);
    boost::asio::ip::tcp::socket& getSocket();
    void start();

protected:
    void handleWrite(const boost::system::error_code& error, size_t);
    void handleRead(const boost::system::error_code& error);
	std::string answerToRequest(const std::string& message);

private:
    Dispatcher& dispatcher_;
    std::unique_ptr<JsonWriter> writer;

    boost::asio::ip::tcp::socket socket;
    std::string message;
    std::vector<char> buf;
    boost::asio::streambuf response_;
};

#endif//TCPCONNECTION_HPP
