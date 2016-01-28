//===----------------------------------------------------------------------===//
//
//
//                       integration of libraries
//
//
//===----------------------------------------------------------------------===//


#include <iostream>
#include "boost/asio.hpp"
#include "wiredtigher/wiredtiger.h"
#include "berkeleydb/db_cxx.h"

using std::cout;
using std::endl;

int main() {
    boost::asio::io_service service;
    cout << "Hello, World!" << endl;
}

//===----------------------------------------------------------------------===//
