//===----------------------------------------------------------------------===//
//
//
//                          string and c-string
//
//
//===----------------------------------------------------------------------===//

#include "36-string.hpp"

using std::cout;
using std::endl;

using std::string;

string address(const string & identifier, const string & domain)
{
    return identifier + '@' + domain;
}

char * address(const char * identifier, const char * domain)
{
    size_t s = strlen(identifier)+strlen(domain)+2;
    char * p = (char*)malloc(s);
    snprintf(p, s, "%s@%s", identifier, domain);
    return p;
}

int main()
{
    string s = address(string("lance"), "hk.orc-group.com");
    cout << s << endl;

    char * t = address("lance", "hk.orcsoftware.com");
    printf("%s\n", t);
    free(t);
}

//===----------------------------------------------------------------------===//
