//===----------------------------------------------------------------------===//
//
//
//                          lambda expressions
//
//      [capture] (parameter) mutable noexcept -> return-type {statement}
//
//
//===----------------------------------------------------------------------===//

#include "11-operations.hpp"

using std::string;
using std::cout;
using std::endl;

#define state (cout << "s = " << s << "; " << "t = " << t << endl)

int main()
{
    //==
    //
    // lambda expression can be assigned to a variable like pointer to function
    //
    //==
    auto expression = [](string s){ cout << s << endl; };
    expression("Hello, Lambda!");

    //==
    //
    // capture: pass by value [=] and pass by reference [&]
    //
    //==
    string s("V");
    string t("R");
    state;

    auto capture = [s, &t](){
        state;

//      s = "value";
        t = "reference";
        state;
    };
    capture();

    state;

    //==
    //
    // return type
    //
    //==
    cout << []() -> string { return "Hello"; }() << endl;
    cout << [](){ return "Lambda"; }() << endl;

}

//===----------------------------------------------------------------------===//
