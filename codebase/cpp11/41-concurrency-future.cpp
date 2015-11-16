//! headers
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <iostream>
#include <random>
#include <future>
#include <thread>
#include <chrono>

//! using declarations
using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::chrono::milliseconds;
using std::future;
using std::async;
using std::this_thread::sleep_for;

//! sleep for a random timeslice then echo
int random_timeslice_echo(char c)
{
	default_random_engine         engine((unsigned int)(c));
	uniform_int_distribution<int> distribution(10, 1000);

	for (int i = 0; i < 10; i++) {
		sleep_for(milliseconds(distribution(engine)));
		cout.put(c).flush();
	}

	return c;
}

int function1() { return random_timeslice_echo('-'); }
int function2() { return random_timeslice_echo('+'); }

//! program entry point
int main()
{
	future<int> result1{async(function1)};
	int result2 = function2();

	int result = result1.get() + result2;

	cout << endl << "reuslt of function1 + function2: " << result << endl;

	return 0;
}

#pragma clang diagnostic pop
