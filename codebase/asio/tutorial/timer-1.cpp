#include <iostream>
#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

int main()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));

    timer.wait();

    std::cout << "Hello, World!" << std::endl;

    return 0;
}
