//===----------------------------------------------------------------------===//
//
//
//                          basic string tempalte
//
// template<typename C,
//          typename T = char_traits<C>,
//          typename A = allocator<C>>
// class basic_string {};
//
//===----------------------------------------------------------------------===//

#include "36-string.hpp"

using std::cout;
using std::endl;

int main()
{

    using string = std::basic_string<char32_t>;

    //==
    //
    // error: no matching constructor for initialization of 'string' (aka 'basic_string<char32_t>')
    //
    //==

    string s("abcd");
    cout << "string: " << s << endl;

    //==
    //
    // error: no matching constructor for initialization of 'std::u32string' (aka 'basic_string<char32_t>')
    //
    //==

    std::u32string t("abdc");
    cout << "string: " << t << endl;

}

//===----------------------------------------------------------------------===//
