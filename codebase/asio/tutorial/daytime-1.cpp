// Daytime.1 - A synchronous TCP daytime client
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

bool is_running = true;

int main(int argc, char *argv[]){
    try {
        if (argc != 2) { std::cerr << "usage: daytimeclient <host>" << std::endl;  return 1; }

        boost::asio::io_service service;

        boost::asio::ip::tcp::resolver resolver(service);
        boost::asio::ip::tcp::resolver::query query(argv[1], "daytime");
        boost::asio::ip::tcp::resolver::iterator endpoint_it = resolver.resolve(query);
        boost::asio::ip::tcp::socket socket(service);

        boost::asio::connect(socket, endpoint_it);

        while (is_running) {

            boost::array<char, 256> buffer;
            boost::system::error_code e;

            size_t size = socket.read_some(boost::asio::buffer(buffer), e);
            if (e == boost::asio::error::eof) break; else if (e) throw boost::system::system_error(e);

            std::cout.write(buffer.data(), size);
        }

        service.run();
    }
    catch(std::exception& e) { std::cout << "exception: " << e.what() << std::endl; }
    return 0;
}
