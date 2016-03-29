#include <ctime>
#include <iostream>
#include <boost/asio.hpp>

using std::string;
using std::cout;
using std::endl;

using boost::asio::ip::tcp;

namespace { using namespace std; string make_daytime_string(){ time_t now = time(0); return ctime(&now); } }
namespace {

class connection: public boo
{
public:
private:
    connection(boost::asio::io_service& s): socket(s), message("uninitialized"){}; ~connection(){};
    tcp::socket socket; string message;
};

class server { public: server(boost::asio::io_service& s):acceptor(s, tcp::endpoint(tcp::v4(), 8888)){}; ~server(){}; private: tcp::acceptor acceptor; };

}

int main()
{
    try {
        boost::asio::io_service service;
        server server(service);
        service.run();
        cout << "The time now is " << make_daytime_string();
    }
    catch (std::exception& e){ cout << "Exception: " << e.what() << endl; }
}
