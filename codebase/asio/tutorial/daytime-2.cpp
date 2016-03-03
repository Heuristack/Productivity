#include <ctime>
#include <iostream>
#include "boost/asio.hpp"

bool is_running = true;

std::string make_daytime_string() { std::time_t now = std::time(0); return ctime(&now); }

int main(){
    try {
        boost::asio::io_service service;
        boost::asio::ip::tcp::acceptor acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8813));

        while(is_running) {
            boost::asio::ip::tcp::socket socket(service);
            acceptor.accept(socket);
            boost::system::error_code ignored_error;

            std::string message = make_daytime_string();

            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }

        service.run();
    }
    catch (std::exception& e) { std::cout << "exception: " << e.what() << std::endl; }
}
