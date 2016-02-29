//===----------------------------------------------------------------------===//
//
//
//                   blocking_tcp_echo_client.cpp
//                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//===----------------------------------------------------------------------===//

//==
//
// headers
//
//==
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

//==
//
// aliases
//
//==
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

using boost::asio::ip::tcp;

//==
//
// constants
//
//==
enum { max_length = 1024 };

//==
//
// entry points
//
//==
int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      cerr << "usage: echo_server <host> <port>" << endl;
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::socket s(io_service);
    tcp::resolver resolver(io_service);
    boost::asio::connect(s, resolver.resolve({argv[1], argv[2]}));

    cout << "Enter message: " << endl;
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = std::strlen(request);

    boost::asio::write(s, boost::asio::buffer(request, request_length));

    char reply[max_length];
    size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, request_length));

    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << endl;

  }
  catch (exception& e)
  {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
//===----------------------------------------------------------------------===//
