//===----------------------------------------------------------------------===//
//
//
//                   blocking_tcp_echo_server.cpp
//                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//===----------------------------------------------------------------------===//

//==
//
// headers
//
//==
#include <iostream>
#include <thread>
#include <boost/asio.hpp>


//==
//
// aliases
//
//==
using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

using std::cout;
using std::cerr;
using std::endl;

using std::thread;
using std::move;


//==
//
// constants
//
//==
const int max_length = 1024;


//==
//
// variables
//
//==
int is_running = true;


//==
//
// program entry point
//
//==
int main(int argc, char* argv[])
{
  try
  {

    if (argc != 2)
    {
      cerr << "usage: echo_server <port>" << endl;
      return 1;
    }

    boost::system::error_code e;

    //==
    //
    // objects used to construct the server
    //
    //==
    unsigned short port = std::atoi(argv[1]);
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

    //==
    //
    // main loop
    //
    //==
    while(is_running){
      boost::asio::ip::tcp::socket s(io_service);
      acceptor.accept(s);

      //==
      //
      // handle connection
      //
      //==
      char d[max_length];

      size_t in = s.read_some(boost::asio::buffer(d), e);
      size_t on = s.write_some(boost::asio::buffer(d, in));

    }

  }
  catch (std::exception& e)
  {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
//===----------------------------------------------------------------------===//
