//===----------------------------------------------------------------------===//
//
//
//                          string operations
//
//
//===----------------------------------------------------------------------===//

#include "36-string.hpp"

using std::cout;
using std::endl;

using std::string;

int main(int argc, char** argv)
try {

    //==
    //
    // comparasion
    //
    //==
    string s = "Hello";
    string t = "World";

    bool e = (s == t);

    cout << "Equality of " << s << " and " << s << ": " << e << "!" << endl;
    cout << "Equality of " << t << " and " << t << ": " << e << "!" << endl;
    cout << "Equality of " << s << " and " << t << ": " << e << "!" << endl;

    cout << s << ((s < t) ? " < " : " >= ") << t << endl;

    //==
    //
    // cantatenation
    //
    //==
    string u = s + t;

    cout << "size:     " << u.size() << endl;
    cout << "length:   " << u.length() << endl;
    cout << "max size: " << u.max_size() << endl;

    //==
    //
    // resize
    //
    //==
    u.resize(2*u.size(), '*');
    cout << u << endl;

    //==
    //
    // pre-allocation 'enough' space (capacity)
    //
    //==
    string v;
    v.reserve(100);
    cout << "size: " << v.size() << " of v!" << endl;
    cout << "capacity: " << v.capacity() << " of v!" << endl;

    //==
    //
    // shrink
    //
    //==
    v.shrink_to_fit();
    cout << "size: " << v.size() << " of v!" << endl;
    cout << "capacity: " << v.capacity() << " of v!" << endl;

    //==
    //
    // allocator
    //
    //==
    auto a = v.get_allocator();

    //==
    //
    // subscripting (excpetion could be thrown from at())
    //
    //==
    char c = u[u.size()];
    cout << c << endl;

    char charactor = u.at(u.size()-1);
    cout << charactor << endl;

    //==
    //
    // front and back
    //
    //==
    cout << "front: " << u.front() << " " << "back: " << u.back() << endl;
    cout << *u.begin() << endl;
    cout << *(u.end() - 1) << endl;

    //==
    //
    // c-string
    //
    //==
    const char *p = u.data();
    cout << p << endl;
    cout << "length: " << strlen(p) << endl;

    //==
    //
    // push and pop
    //
    //==
    u.push_back('!');
    cout << u << endl;
    for (int i = 0; i <= 10; i++) u.pop_back();
    cout << u << endl;

    //==
    //
    // append
    //
    //==
    u.append(string("!"));
    cout << u << endl;
    u += '!';
    cout << u << endl;

    //==
    //
    // swap
    //
    //==
    std::swap(s,t);
    cout << s << endl;
    cout << t << endl;

    s.swap(t);
    cout << s << endl;
    cout << t << endl;

    //==
    //
    // copy (write c-string)
    //
    //==
    char buffer[100]; memset(buffer, 0, 100);

    size_t n = u.copy(buffer, u.size()-2, 0);
    cout << "buffer: " << buffer << ": " << n << ":" << u.size() << endl;

}
catch (std::exception & e)
{
    cout << "exception: " << e.what() << endl;
}


//===----------------------------------------------------------------------===//
