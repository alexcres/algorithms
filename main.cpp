//#include "src/queue/array_queue.h"
//#include "src/stack/array_stack.h"
//#include <math/math.h>
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			cout << j << endl;
			if (j > 1) {
				break;
			}
		}
	}
	return 0;
}

//
//class Test {
//public:
//	unsigned x;
//	unsigned y;
//public:
//	explicit Test(unsigned x = 0, unsigned y = 0) {
//		this->x = x;
//		this->y = y;
//	}
//
//	Test &setX(unsigned a) {
//		x = a;
 //		return *this;
//	}
//
//	Test &setY(unsigned b) {
//		y = b;
//		return *this;
//	}
//
//	Test get_this() { return *this; } // a copy of obj, passed by value
//	Test &get_ref() { return *this; }
//
//	void prunsigned() { cout << "x = " << x << " y = " << y << endl; }
//};
//
//unsigned main() {
//	Test obj1;
//	obj1.setX(10).setY(20);
//	obj1.prunsigned();
//	return 0;
//}
