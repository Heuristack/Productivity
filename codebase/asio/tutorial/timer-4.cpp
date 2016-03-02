// Timer.4 - Using a member function as a handler

#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"


class printer
{
public:
    printer(boost::asio::io_service& service)
        : timer(service, boost::posix_time::seconds(1)), count(0)
    {
        timer.async_wait(boost::bind(&printer::print, this));
    }
    ~printer(){ std::cout << "Final count: " << count << std::endl; }

    void print()
    {
        if (count < 5)
        {
            std::cout << count << std::endl;
            ++count;

            timer.expires_at(timer.expires_at() + boost::posix_time::seconds(1));
            timer.async_wait(boost::bind(&printer::print, this));
        }
    }

private:
    boost::asio::deadline_timer timer;
    int count;
};

int main()
{
    boost::asio::io_service s;
    printer p(s);
    s.run();
    return 0;
}
