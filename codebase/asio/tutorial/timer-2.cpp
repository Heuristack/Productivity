#include <iostream>
#include "boost/asio.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

void print(const boost::system::error_code& /*e*/)
{
    std::cout << "Hello, World!" << std::endl;
}

int main()
{
    boost::asio::io_service service;
    boost::asio::deadline_timer timer(service, boost::posix_time::seconds(5));

    timer.async_wait(&print);

    service.run();

    return 0;
}
