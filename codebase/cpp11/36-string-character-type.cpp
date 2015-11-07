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


    char character = '0';

    if (std::isdigit(character))
        cout << '\'' << character << '\'' << " is a digit!" << endl;


    char &character_reference = character;
    character_reference = 'R';

    if (std::isalpha(character_reference)) {
        character_reference = static_cast<char>(std::tolower(character_reference));
        cout << '\'' << character_reference << '\'' << " should be in lower case!" << endl;
    }

    char SOH = static_cast<char>(0x01);
    if (std::iscntrl(SOH)) {
        cout << (int)SOH << " is an control character!" << endl;
    }

    return 0;
}

//===----------------------------------------------------------------------===//
