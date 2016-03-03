// Timer.5 - Synchronising handlers in multithreaded programs

#include <iostream>
#include "boost/bind.hpp"
#include "boost/thread/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/asio.hpp"

class printer
{
public:

    printer(boost::asio::io_service& s) : strand(s), timer1(s, boost::posix_time::seconds(1)), timer2(s, boost::posix_time::seconds(1)), count(0) { std::cout << "CT: " << std::endl; }

    void print1()
    {
        if (count < 10)
        {
            std::cout << "Timer 1: " << count << std::endl;
            ++count;

            timer1.expires_at(timer1.expires_at() + boost::posix_time::seconds(1));
            timer1.async_wait(strand.wrap(boost::bind(&printer::print1, this)));
        }
    }

    void print2()
    {
        if (count < 10)
        {
            std::cout << "Timer 2: " << count << std::endl;
            ++count;

            timer2.expires_at(timer2.expires_at() + boost::posix_time::seconds(1));
            timer2.async_wait(strand.wrap(boost::bind(&printer::print2, this)));
        }
    }

    ~printer(){ std::cout << "DT: final cout is " << count << std::endl;}

private:
    boost::asio::io_service::strand strand;
    boost::asio::deadline_timer timer1;
    boost::asio::deadline_timer timer2;
    int count;
};

int main()
{
    boost::asio::io_service s;
    printer p(s);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &s));
    s.run();
    t.join();
    return 0;
}
