#include "tcpcontrolconnection.hpp"

TcpControlConnection::TcpControlConnection(boost::asio::io_service& service,
                                           Dispatcher& dispatcher)
    : socket_(service), dispatcher_(dispatcher), isConnected_(false) {
    buf_.resize(2048);

    //    for (auto str : dispatcher_.getMethodNames())
    //        std::cout << str << std::endl;
}

TcpControlConnection::~TcpControlConnection() {}

TcpControlConnection::TcpControlConnectionPtr TcpControlConnection::create(
    boost::asio::io_service& service,
    Dispatcher& dispatcher) {
    return std::make_shared<TcpControlConnection>(service, dispatcher);
}

boost::asio::ip::tcp::socket& TcpControlConnection::getSocket() {
    return socket_;
}

void TcpControlConnection::start() {
    std::cout << "I am in start!!" << std::endl;
    isConnected_ = true;
    //	async_write(socket, boost::asio::buffer(message),
    //				boost::bind(&TcpConnection::handleWrite,
    // shared_from_this(),
    //							boost::asio::placeholders::error,
    //							boost::asio::placeholders::bytes_transferred));

    //    boost::asio::async_read(
    //        socket, boost::asio::buffer(buf_),
    //        boost::bind(&TcpControlConnection::handleRead, shared_from_this(),
    //                    boost::asio::placeholders::error));

    boost::asio::async_read_until(
        socket_, response_, '\n',
        boost::bind(&TcpControlConnection::handleRead, shared_from_this(),
                    boost::asio::placeholders::error));
}

bool TcpControlConnection::isConnected() const {
    return isConnected_;
}

void TcpControlConnection::handleWrite(const boost::system::error_code& error,
                                       size_t) {
    std::cout << "I have wrriten that!!" << std::endl;
}

void TcpControlConnection::handleRead(const boost::system::error_code& error) {
    std::cout << error.message() << std::endl;
    //	if (error != 0)	{
    //		return;
    //	}

    //    std::cout << buf_.size() << std::endl;
    //    std::cout << std::string(buf_.begin(), buf_.end()) << std::endl;
    boost::asio::async_read_until(
        socket_, response_, '\n',
        boost::bind(&TcpControlConnection::handleRead, shared_from_this(),
                    boost::asio::placeholders::error));

    std::istream respStream(&response_);
    std::string msg(std::istreambuf_iterator<char>(respStream), {});
    std::cout << msg << std::endl;
    if (msg == std::string(""))
        return;

    boost::asio::async_write(
        socket_, boost::asio::buffer(answerToRequest(msg)),
        boost::bind(&TcpControlConnection::handleWrite, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

std::string TcpControlConnection::answerToRequest(const std::string& message) {
    writer_ = std::unique_ptr<JsonWriter>(new JsonWriter());

    try {
        auto reader = std::unique_ptr<JsonReader>(new JsonReader(message));
        Request request = reader->getRequest();
        reader.reset();

        auto response = dispatcher_.Invoke(
            request.getMethodName(), request.getParameters(), request.getId());
        response.write(*writer_.get());
    } catch (const Fault& ex) {
        Response(ex.GetCode(), ex.GetString(), Value()).write(*writer_.get());
    }

    std::cout << writer_->getData() << std::endl;

    return writer_->getData();
}
