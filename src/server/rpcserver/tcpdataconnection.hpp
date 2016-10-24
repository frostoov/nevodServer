#ifndef TCPDATACONNECTION_HPP
#define TCPDATACONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

class TcpDataConnection
    : public std::enable_shared_from_this<TcpDataConnection> {
public:
    using TcpDataConnectionPtr = std::shared_ptr<TcpDataConnection>;

    TcpDataConnection(boost::asio::io_service& service);
    ~TcpDataConnection();

    static TcpDataConnectionPtr create(boost::asio::io_service& service);
    boost::asio::ip::tcp::socket& getSocket();
    void start();
    bool isConnected() const;

    bool sendData(const std::vector<uint8_t>& data);

protected:
    void handleWrite(const boost::system::error_code& error, size_t);

private:
    boost::asio::ip::tcp::socket socket_;
    bool isConnected_;
};

#endif//TCPDATACONNECTION_HPP
