//===----------------------------------------------------------------------===//
//
//
//                       integration of libraries
//
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "boost/asio.hpp"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    boost::asio::io_service service;

    cout << "Hello, World!" << endl;

    return 0;
}

//===----------------------------------------------------------------------===//
