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
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
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

//==
//
// global variables
//
//==
const int max_length = 1024;

//==
//
// global functions
//
//==
void session(tcp::socket sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof) break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      boost::asio::write(sock, boost::asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    cerr << "Exception in thread: " << e.what() << endl;
  }
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    std::thread(session, std::move(sock)).detach();
  }
}

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
      cerr << "Usage: blocking_tcp_echo_server <port>" << endl;
      return 1;
    }

    boost::asio::io_service io_service;

    server(io_service, std::atoi(argv[1]));
  }
  catch (std::exception& e)
  {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
//===----------------------------------------------------------------------===//
