#include <iostream>
#include <boost/array.hpp>
#include <asio.hpp>

using asio::ip::tcp;
using namespace std;

int main(int args, char* argv[]) {
    try{
        if(argc != 2) {
            std::cerr << "Usage client <host>" << endl;
            return 1;
        }
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "exam_paper_bank_management"); //host name + self-defined service name
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);
        for(;;) {
            boost::array<char, 128> buf;
            asio::error_code error;
            size_t len = socket.read_some(asio::buffer(buf), error);
            if(error == asio::error::eof) break;
            else if(error) throw asio::system_error(error);
            std::cout.write(buf.data(), len);
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}