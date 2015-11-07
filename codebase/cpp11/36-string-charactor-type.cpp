//===----------------------------------------------------------------------===//
//
//
//                     character classification (types)
//
//
//===----------------------------------------------------------------------===//

#include "36-string.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv) {


    char charactor = '0';

    if (std::isdigit(charactor))
        cout << '\'' << charactor << '\'' << " is a digit!" << endl;


    char & charactor_reference = charactor;
    charactor_reference = 'R';

    if (std::isalpha(charactor_reference)) {
        charactor_reference = static_cast<char>(std::tolower(charactor_reference));
        cout << '\'' << charactor_reference << '\'' << " should be in lower case!" << endl;
    }

    char SOH = static_cast<char>(0x01);
    if (std::iscntrl(SOH)) {
        cout << (int)SOH << " is an control charactor!" << endl;
    }

    return 0;
}

//===----------------------------------------------------------------------===//
