//===----------------------------------------------------------------------===//
//
//
//                          string operations
//
//
//===----------------------------------------------------------------------===//
//! headers
#include <stdio.h>
#include <initializer_list>
#include <string>
#include <iostream>

//! 'using' declarations
using std::printf;
using std::string;
using std::cout;
using std::endl;

//! program entry point
int main()
{
	cout << ">>>>> enter: unit case for string class >>>>>" << endl;

	// create through constructors
	const string s ("Life is like riding a bicycle.");				// string(C-string)
	const string t = "To keep your balance you must keep moving.";	// copy initialization
	cout << s << ' ' << t << endl;

	// default constructor and assignment
	std::string u;
	(u = s).append(t);
	u.insert(s.size(), " ");
	cout << u << endl;

	// copy construction
	string v(s);
	(v += " ") += t;
	cout << v << endl;

	// concatination
	string w(s + " " + t);
	cout << w << endl;

	// access through rang-for [C++11]
	for (auto c : s) cout << c; cout << ' ';
	for (auto c : t) cout << c; cout << endl;

	// access through iterator
	for (auto it = s.begin(); it != s.end(); it++) cout << *it; cout << ' ';
	for (auto it = t.begin(); it != t.end(); it++) cout << *it; cout << endl;

	// access through operator
	for (int i = 0; i < s.size(); i++) cout << s[i]; cout << ' ';
	for (int i = 0; i < t.size(); i++) cout << t[i]; cout << endl;

	// access through C-string
	printf("%s %s\n", s.data(), t.c_str());

	// access front and back
	printf("front: %c; back: %c;\n", s.front(), t.back());

	// clear contents
	cout << "v.size before clear: " << v.size() << endl;
	v.clear();
	cout << "v.size after  clear: " << v.size() << endl;

	// C-string constructor
	char *p = NULL;
	p = (char *)::malloc(sizeof(char)*0xff);
	snprintf(p, 0xff, "Life is like riding a bicycle.");
	string ps(p);
	cout << p << endl;

	cout << "<<<<< leave: unit case for string class <<<<<" << endl;
}
//===----------------------------------------------------------------------===//
