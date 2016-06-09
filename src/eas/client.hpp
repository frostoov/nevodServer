#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <thread>
#include <memory>
#include <cstdint>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../observer/observer.hpp"

class Client : public Subject, public std::enable_shared_from_this<Client> {
public:
    using IoServicePtr = std::shared_ptr<boost::asio::io_service>;

    enum class Message { connected, disconnected, readyRead, error, null };

    explicit Client(const std::string& ip,
                    uint16_t port,
                    const IoServicePtr& service);
    ~Client();

    bool connectToHost();
    bool disconnectFromHost();
    void readRegister(uint32_t address);
    void writeRegister3000(uint32_t address, uint32_t data);
    void writeRegister3002(uint32_t address, uint32_t data);
    bool isStopped() const;
    void clearData();

    const std::vector<uint8_t>& getData() const;
    Message getMessage() const;

    void write(int32_t number, bool isBan) {}

protected:
    void startConnect();
    void startRead();
    void startWrite(const std::vector<char>& message);
    void connectHandler(const boost::system::error_code& error);
    void readHandler(const boost::system::error_code& error, size_t);
    void writeHandler(const boost::system::error_code& error, size_t);
    void checkDeadline();

private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf inputBuffer_;
    boost::asio::deadline_timer deadlineTimer_;
    boost::asio::deadline_timer heartbeatTimer_;
    std::string ip_;
    uint16_t port_;
    bool stopped_;
    std::vector<uint8_t> data_;
    Message message_;
};

#endif  // CLIENT_HPP
