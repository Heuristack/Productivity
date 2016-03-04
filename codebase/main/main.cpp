//===----------------------------------------------------------------------===//
//
//
//                       integration of libraries
//
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "boost/asio.hpp"
#include "quickfix/SessionSettings.h"
#include "quickfix/Application.h"
#include "ql/quantlib.hpp"
#include "db_cxx.h"
#include "dispatch/dispatch.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
try
{

    cout << "Hello, World!" << endl;


    boost::asio::io_service io;
    io.run();


    FIX::SessionSettings settings("session.config");


    cout << "QuantLib Version: " << QL_LIB_VERSION << endl;


    Db db(NULL, 0);
    db.open(NULL, "universe.db", NULL, DB_BTREE, DB_CREATE, 0);
    db.close(0);

}
catch (FIX::ConfigError& e)
{
    cout << "FIX exception: " << e.what() << endl;
}
catch (DbException& e)
{
    cout << "BDB exception: " << e.what() << endl;
}
catch (std::exception & e)
{
    cout << "exception: " << e.what() << endl;
}

//===----------------------------------------------------------------------===//
