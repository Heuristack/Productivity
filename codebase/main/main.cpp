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
#include "berkeleydb/db_cxx.h"
#include "dispatch/dispatch.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
try
{

    cout << "Hello, World!" << endl;

    boost::asio::io_service io;
    io.run();


    try { FIX::SessionSettings settings("session.config"); } catch (FIX::ConfigError& e){ cout << "Exception@FIX: Configuration Error: " << e.what() << endl; }

    cout << "QuantLib Version: " << QL_LIB_VERSION << endl;

    try { Db db(NULL, 0); db.open(NULL, "universe.db", NULL, DB_BTREE, DB_CREATE, 0); db.close(0); } catch (DbException& e) { cout << "Exception@BDB: " << e.what() << endl; }

}
catch (std::exception & e)
{
    cout << "Exception: " << e.what() << endl;
}

//===----------------------------------------------------------------------===//
