#include "Timer.h"

using namespace std;

int main() {
	Timer<chrono::microseconds> t1("Timer1");
	Timer<> t2("Timer2");
	Timer<chrono::milliseconds> t3;

	cout << t3.getTime() << endl;
	t2.printTime();
	cout << t1 << endl;

	return 0;
}