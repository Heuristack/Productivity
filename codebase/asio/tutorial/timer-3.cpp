//Timer.3 - Binding arguments to a handler

#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

void print(const boost::system::error_code& e, boost::asio::deadline_timer* t, int*c)
{
    if (*c < 5)
    {
        std::cout << *c << std::endl;
        ++(*c);
        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, c));
    }
}

int main()
{
    boost::asio::io_service service;
    boost::asio::deadline_timer timer(service, boost::posix_time::seconds(1));
    int count = 0;

    timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));

    service.run();

    std::cout << "Final count: " << count << std::endl;

    return 0;
}
