#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enabled_shared_from_this.hpp>
#include <asio.hpp>

using asio::ip::tcp;
using namespace std;

class tcp_server {
    public:
        tcp_server(asio::io_context& io_context): io_context_(io_context),
                                                  acceptor_(io_context, tcp::endpoint(tcp::v4(), 9999)){
                                                    start_accept();
                                                  }
        void set_message(string&& message) {
            strcpy(message_, message);
        }
    private:
        void start_accept() {
            tcp_connection::pointer_new_connection = tcp::connection::create(io_context_);
            acceptor_.async_accept(new_connection->socket(), boost::bind(&tcp_server::handle_accept, this, new_connection,
            asio::placeholders::error));
        }
        void handle_accept(tcp_connection::pointer new_connection, const asio::error_code& error) {
            if(!error) {new_connection->start(message_);}
            start_accept();
        }
        asio::io_context& io_context_;
        tcp::acceptor acceptor_;
        string message_;

};

class tcp_connection: public boost::enabled_shared_from_this<tcp_connection> {
    public:
        typedef boost::shared_ptr<tcp_connection> pointer;
        static pointer create(asio::io_context& io_context) {
            return pointer(new tcp_connection(io_context));
        }
        tcp::socket& socket() {
            return socket_;
        }
        void start(string&& message_) {
            asio::async_write(socket_, asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this()));
            //asio::placeholders::error,
            //asio::placeholders::bytes_transferred));
        }
        
    private:
        tcp::connection(asio::io_context& io_context): socket_(io_context) {}
        // void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/) {}
        void handle_write() {}
        tcp::socket socket_;
};

int main() {
    try {
        asio::io_context io_context;
        tcp_server server(io_context);
        string message = "dummy message";
        server.set_message(message);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}