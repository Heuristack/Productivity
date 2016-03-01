//===----------------------------------------------------------------------===//
//
//
//                                program
//
//
//===----------------------------------------------------------------------===//

//==
//
// headers
//
//==
#include <iostream>
#include <thread>

//==
//
// aliases
//
//==
using std::cout;
using std::endl;
using std::string;

//==
//
// constants
//
//==
const string seperator = "!";
const string endofline = "\n";

//==
//
// variables
//
//==
string non_constant = "non-constant";
unsigned int stack_counter = 0;


//==
//
// unnamed namespace (Translation-Unit-Local)
//
//==
namespace {

string s = "Hello, unnamed namespace";

class x {
public:
    static const string s;
};

const string x::s = "(unnamed namespace)::x::";

}//namespace


//==
//
// entry point (main can also call main)
//
//==
int main()
{
    //==
    //
    // thread_local is not supported by Apple clang
    //
    //==
    // thread_local int threadlocalx = 1;

    stack_counter++;
    cout << "stack depth: " << stack_counter << endofline;
    cout << x::s << s << seperator << non_constant << endl;
}
//===----------------------------------------------------------------------===//

