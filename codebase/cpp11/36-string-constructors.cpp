//===----------------------------------------------------------------------===//
//
//
//                              string constructors
//
//
//===----------------------------------------------------------------------===//


#include "36-string.hpp"

using std::cout;
using std::endl;

using std::string;

int main()
{

    const char* p = nullptr;
    p = "error if p points to a non-c-string";

    string s0;                              // string() - default
    string s1 {"a simple string"};          // string(const char*)
    string s2 {s1};                         // string(string) - copy
    string s3 {1};                          // string(int)
    string s4 {'a'};                        // string(char)
    string s5 {8,'a'};                      // string
    string s6 {0};                          // string(char*)
    string s7 {p};                          // string(char*)
    string s8 {"OK"};                       // string(const char*)
//  string s9 {string::npos, 'a'};          // npos represents position beyond a string

    string t0 {"MacBook Air"};
    string t1 {t0, 0, 6};
    string t2 {t0, 8, string::npos};

    cout << "s0: [" << s0 << "]" << " : " << s0.size() << " / " << s0.max_size() << endl;
    cout << "s1: [" << s1 << "]" << " : " << s1.size() << " / " << s1.max_size() << endl;
    cout << "s2: [" << s2 << "]" << " : " << s2.size() << " / " << s2.max_size() << endl;
    cout << "s3: [" << s3 << "]" << " : " << s3.size() << " / " << s3.max_size() << endl;
    cout << "s4: [" << s4 << "]" << " : " << s4.size() << " / " << s4.max_size() << endl;
    cout << "s5: [" << s5 << "]" << " : " << s5.size() << " / " << s5.max_size() << endl;
    cout << "s6: [" << s6 << "]" << " : " << s6.size() << " / " << s6.max_size() << endl;
    cout << "s7: [" << s7 << "]" << " : " << s7.size() << " / " << s7.max_size() << endl;
    cout << "s8: [" << s8 << "]" << " : " << s8.size() << " / " << s8.max_size() << endl;
//  cout << "s9: [" << s9 << "]" << " : " << s9.size() << " / " << s9.max_size() << endl;

    cout << "t0: [" << t0 << "]" << " : " << t0.size() << " / " << t0.max_size() << endl;
    cout << "t1: [" << t1 << "]" << " : " << t1.size() << " / " << t1.max_size() << endl;
    cout << "t2: [" << t2 << "]" << " : " << t2.size() << " / " << t2.max_size() << endl;

    return 0;
}

//===----------------------------------------------------------------------===//

