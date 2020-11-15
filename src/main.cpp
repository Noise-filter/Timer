#include "Timer.h"

#include <thread>
#include <future>
#include <sstream>

using namespace std;

void timeThisFunction() {
	ScopedTimer<chrono::microseconds> timer("timeThisFunction timer");
	this_thread::sleep_for(1ms);
}

int main() {
	Timer<> timer("Timer overhead");
	timer.printTime();

	stringstream sstream;
	{
		ScopedTimer<> scopedTimer("Scoped timer", sstream);
	}

	Timer<chrono::microseconds> t1("Timer1");
	Timer<> t2("Timer2");
	Timer<chrono::milliseconds> t3;
	t2.printTime();
	cout << t1 << endl;

	cout << "String stream " << sstream.str();
	{
		ScopedTimer<chrono::microseconds> asyncTimer("Function timer");
		timeThisFunction();
	}
	{
		ScopedTimer<chrono::microseconds> asyncTimer("Async Timer");
		auto future = async(launch::async, timeThisFunction);
		future.wait();
	}


	auto t3Time = t3.getTime();
	cout << t3Time << endl;

	return 0;
}