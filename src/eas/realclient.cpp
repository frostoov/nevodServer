#include "realclient.hpp"

#include <iostream>  //TODO

RealClient::RealClient(const std::string& ip,
                       uint16_t port,
                       const IoServicePtr& service)
    : socket_(*(service.get())),
      ip_(ip),
      port_(port),
      stopped_(true),
      deadlineTimer_(*(service.get())),
      heartbeatTimer_(*(service.get())) {
    message_ = Message::error;
}

RealClient::~RealClient() {}

bool RealClient::connectToHost() {
    stopped_ = false;
    startConnect();

    //    deadlineTimer_.async_wait(
    //                boost::bind(&RealClient::checkDeadline,
    //                shared_from_this()));
}

bool RealClient::disconnectFromHost() {
    stopped_ = true;
    socket_.close();
    deadlineTimer_.cancel();
    heartbeatTimer_.cancel();
    return true;
}

void RealClient::readRegister(uint32_t address) {
    std::vector<char> sendMessage;
    sendMessage.resize(12);
    sendMessage[0] = 0x0b;
    sendMessage[1] = 0xb9;

    sendMessage[2] = 0x0b;
    sendMessage[3] = 0xb9;

    sendMessage[4] = 0;
    sendMessage[5] = 12;

    sendMessage[6] = 0;
    sendMessage[7] = 0;

    sendMessage[8] = address & 0xff;
    sendMessage[9] = (address >> 8) & 0xff;

    sendMessage[10] = (address >> 16) & 0xff;
    sendMessage[11] = (address >> 24) & 0xff;

    startWrite(sendMessage);
}

void RealClient::writeRegister3000(uint32_t address, uint16_t data) {
    std::vector<char> sendMessage;
    sendMessage.resize(14);
    sendMessage[0] = 0x0b;
    sendMessage[1] = 0xb8;

    sendMessage[2] = 0x0b;
    sendMessage[3] = 0xb8;

    sendMessage[4] = 0;
    sendMessage[5] = 14;

    sendMessage[6] = 0;
    sendMessage[7] = 0;

    sendMessage[8] = address & 0xff;
    sendMessage[9] = (address >> 8) & 0xff;

    sendMessage[10] = (address >> 16) & 0xff;
    sendMessage[11] = (address >> 24) & 0xff;

    sendMessage[12] = data & 0xff;
    sendMessage[13] = (data >> 8) & 0xff;

    startWrite(sendMessage);
}

void RealClient::writeRegister3002(uint32_t address, uint16_t data) {
    std::vector<char> sendMessage;
    sendMessage.resize(14);
    sendMessage[0] = 0x0b;
    sendMessage[1] = 0xba;

    sendMessage[2] = 0x0b;
    sendMessage[3] = 0xba;

    sendMessage[4] = 0;
    sendMessage[5] = 14;

    sendMessage[6] = 0;
    sendMessage[7] = 0;

    sendMessage[8] = address & 0xff;
    sendMessage[9] = (address >> 8) & 0xff;

    sendMessage[10] = (address >> 16) & 0xff;
    sendMessage[11] = (address >> 24) & 0xff;

    sendMessage[12] = data & 0xff;
    sendMessage[13] = (data >> 8) & 0xff;

    startWrite(sendMessage);
}

bool RealClient::isStopped() const {
    return stopped_;
}

void RealClient::clearData() {
    data_.clear();
}

const std::vector<uint8_t>& RealClient::getData() const {
    return data_;
}

RealClient::Message RealClient::getMessage() const {
    return message_;
}

void RealClient::startConnect() {
    //    deadlineTimer_.expires_from_now(boost::posix_time::seconds(60));
    boost::asio::ip::tcp::endpoint ep(
        boost::asio::ip::address::from_string(ip_), port_);
    socket_.async_connect(
        ep, boost::bind(&RealClient::connectHandler, shared_from_this(),
                        boost::asio::placeholders::error));
//    boost::asio::async_connect(
//        socket_, ep,
//        boost::bind(&RealClient::connectHandler, shared_from_this(),
//                    boost::asio::placeholders::error));
}

void RealClient::startRead() {
    //	deadlineTimer_.expires_from_now(boost::posix_time::seconds(30));

    boost::asio::async_read_until(
        socket_, inputBuffer_, '\n',
        boost::bind(&RealClient::readHandler, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RealClient::startWrite(const std::vector<char>& message) {
    if (stopped_)
        return;

    boost::asio::async_write(
        socket_, boost::asio::buffer(message),
        boost::bind(&RealClient::writeHandler, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void RealClient::connectHandler(const boost::system::error_code& error) {
    if (stopped_)
        return;
    if (!error) {
        startRead();
        //		startWrite();
    }
}

void RealClient::readHandler(const boost::system::error_code& error, size_t) {
    if (stopped_)
        return;

    std::cout << "Reading:\t" << error.message() << std::endl;

    if (!error) {
        std::string line;
        std::istream is(&inputBuffer_);
        std::getline(is, line);

        if (!line.empty())
            std::cout << "Received: " << line << std::endl;

        startRead();
    } else {
        std::cout << "Error reading" << std::endl;
        disconnectFromHost();
    }
}

void RealClient::writeHandler(const boost::system::error_code& error, size_t) {
    if (stopped_)
        return;

    std::cout << "Writing:\t" << error.message() << std::endl;

    if (!error) {
        //		heartbeatTimer_.expires_from_now(boost::posix_time::seconds(10));
        //		heartbeatTimer_.async_wait(boost::bind(&Client::startWrite,
        // shared_from_this()));
    } else {
        std::cout << "Error writing" << std::endl;
        disconnectFromHost();
    }
}

// void RealClient::checkDeadline() {
//	if (stopped_)
//		return;
//	std::cout << "Deadline" << std::endl;
//	if (deadlineTimer_.expires_at() <=
//		boost::asio::deadline_timer::traits_type::now()) {
//		socket_.close();
//		deadlineTimer_.expires_at(boost::posix_time::pos_infin);
//	}
//	deadlineTimer_.async_wait(
//		boost::bind(&RealClient::checkDeadline, shared_from_this()));
//}
