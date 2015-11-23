//===----------------------------------------------------------------------===//
//
//
//                                 string
//
//
//===----------------------------------------------------------------------===//

#include "31-containers.hpp"
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;


struct s
{
    string tag;
    double val;

    s() : tag(""), val(.0) {}
    s(string t, double v) : tag(t), val(v) {}
};


int main()
{

    vector<s> vs;
    vs.push_back(s("version", 1.1));
    vs.push_back(s("version", 2.1));

    for (auto element : vs) cout << element.tag << ": " << element.val << endl;

}

//===----------------------------------------------------------------------===//

