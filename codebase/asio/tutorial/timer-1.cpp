// Timer.1 - Using a timer synchronously

#include <iostream>
#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

int main()
{
    boost::asio::io_service service;
    boost::asio::deadline_timer timer(service, boost::posix_time::seconds(5));

    timer.wait();

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
