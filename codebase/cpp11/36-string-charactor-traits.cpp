//===----------------------------------------------------------------------===//
//
//
//                          charactor properties
//
//                  template<typename T> struct char_traits{};
//
//===----------------------------------------------------------------------===//


#include "36-string.hpp"

using std::cout;
using std::endl;

using std::string;
using std::char_traits;

int main()
{

    //==
    //
    // members of char_traits<> are all static functions
    //
    //==
    typedef char_traits<char> charactor_properties;

    char a = 'a';
    char b = 'b';

    bool equal = charactor_properties::eq(a, b);

    cout << '\'' << a << '\'' << " and " << '\'' << b << '\'' << " are " << equal << " equal!";
}

//===----------------------------------------------------------------------===//
