#include "tcpconnection.hpp"

#include <iostream>  //TODO

TcpConnection::TcpConnection(boost::asio::io_service& service,
                             Dispatcher& dispatcher)
    : socket(service), dispatcher_(dispatcher) {
    //	formatHandler = std::make_shared<JsonFormatHandler>();
    buf.resize(2048);

    for (auto str : dispatcher_.getMethodNames())
        std::cout << str << std::endl;
}

TcpConnection::~TcpConnection() {}

TcpConnection::TcpConnectionPtr TcpConnection::create(
    boost::asio::io_service& service,
    Dispatcher& dispatcher) {
    return std::make_shared<TcpConnection>(service, dispatcher);
}

boost::asio::ip::tcp::socket& TcpConnection::getSocket() {
    return socket;
}

void TcpConnection::start() {
    std::cout << "I am in start!!" << std::endl;

    //	async_write(socket, boost::asio::buffer(message),
    //				boost::bind(&TcpConnection::handleWrite,
    //shared_from_this(),
    //							boost::asio::placeholders::error,
    //							boost::asio::placeholders::bytes_transferred));

    //	boost::asio::async_read(socket, boost::asio::buffer(buf),
    //									boost::bind(&TcpConnection::handleRead,
    //shared_from_this(),
    //													boost::asio::placeholders::error,
    //													boost::asio::placeholders::bytes_transferred));

    boost::asio::async_read_until(
        socket, response_, ";",
        boost::bind(&TcpConnection::handleRead, shared_from_this(),
                    boost::asio::placeholders::error));
}

void TcpConnection::handleWrite(const boost::system::error_code& error,
                                size_t) {
    std::cout << "I have wrriten that!!" << std::endl;
    //	boost::asio::async_read_until(socket, response_, ";",
    //									boost::bind(&TcpConnection::handleRead,
    //shared_from_this(),
    //													boost::asio::placeholders::error
    //													));
}

void TcpConnection::handleRead(const boost::system::error_code& error) {
    std::cout << error.message() << std::endl;
    //	if (error != 0)	{
    //		return;
    //	}

    //	std::cout << buf.size() << std::endl;
    //	std::cout << std::string(buf.begin(), buf.end()) << std::endl;

    std::istream respStream(&response_);
    std::string msg(std::istreambuf_iterator<char>(respStream), {});
    msg.erase(msg.end() - 1);
    std::cout << msg << std::endl;

    writer = std::unique_ptr<JsonWriter>(new JsonWriter());

    try {
        auto reader = std::unique_ptr<JsonReader>(new JsonReader(msg));
        Request request = reader->getRequest();
        reader.reset();

        auto response = dispatcher_.Invoke(
            request.getMethodName(), request.getParameters(), request.getId());
        response.write(*writer.get());
    } catch (const Fault& ex) {
        Response(ex.GetCode(), ex.GetString(), Value()).write(*writer.get());
    }

    std::cout << writer->getData() << std::endl;

    boost::asio::async_write(
        socket, boost::asio::buffer(std::string(writer->getData())),
        boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}
