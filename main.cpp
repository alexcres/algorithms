//#include "src/queue/array_queue.h"
//#include "src/stack/array_stack.h"
//#include <math/math.h>
//#include "./src/util.h"
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <functional>
#include <zconf.h>
#include <cstring>
#include <bitset>
#include <cassert>

#include "stdio.h"

using namespace std;

#define KEYWORDS 01
#define EXTERNAL 02
#define ALLOCSIZE 10000
static char allocbuff[ALLOCSIZE];
static char *allocp = allocbuff;

char *alloc(int n) {
	if (allocp + n <= allocbuff + ALLOCSIZE) {
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

void free(char *p) {
	if (p >= allocbuff && p <= allocbuff + ALLOCSIZE) {
		allocp = p;
	}
}

void fprint(char *fmt, ...) {
	va_list vp;
	int ival;
	double dval;
	char *sval;
	va_start(vp, fmt);
	for (; *fmt; ++fmt) {
		if (*fmt != '%') {
			putchar(*fmt);
			continue;
		}
		switch (*++fmt) {
			case 'd':
				ival = va_arg(vp, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(vp, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(vp, char*); *sval; ++sval)
					putchar(*sval);
				break;
			default:
				break;
		}
	}
}

int b_search(int needle, vector<int> pool) {
	auto start = pool.cbegin();
	auto end = pool.cend();
	auto mid = start + (end - start) / 2;

	while (mid != end && (*mid) != needle) {
		if (needle < *mid) {
			end = mid;
		} else {
			start = mid + 1;
		}
		mid = start + (end - start) / 2;
	}
	return *mid;
}

unsigned fact(unsigned n) {
	unsigned res = 1;
	while (n > 1) {
		res *= n;
		--n;
	}
	return res;
}

int count() {
	static int counter = 0;
	return ++counter;
}

void p_swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void ref_swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void reset(int &n) {
	n = 0;
}

int bigger(int a, const int *p) {
	if (a > *p) {
		return a;
	} else {
		return *p;
	}
}

void print(initializer_list<string> ls) {
	for (const auto &l : ls) {
		cout << l << " ";
	}
}

string test() {
	return "fasfadsf";
}

unsigned re_fact(unsigned n) {
	if (n != 1) {
		return n * re_fact(n - 1);
	}
	return 1;
}

string s[10];

//Write the declaration for a function that returns a reference to an array
//of ten strings
string (&func(string (&s)[10]))[10];

//One should use a type alias, one should use a trailing return, and the third
//should use decltype.
using mystring = string[10];

mystring &func2(mystring &s);

auto func3(string (&s)[10]) -> string (&)[10];

decltype(s) &func4(decltype(s) &s);

int pfun(int a, int b);
using Fun = decltype(pfun);

int add(int a, int b) {
	return a+b;
}
int subtract(int a, int b) {
	return a - b;
}
int multiply(int a, int b) {
	return a * b;
}
int main(int argc, char *argv[]) {
	vector<Fun *> v;
	v.push_back(add);
	v.push_back(subtract);
	v.push_back(multiply);

	int a, b;
	while (cin >> a >> b) {
		assert(b != 0);
		for (auto action: v) {
			cout << action(a, b) << endl;
		}
	}
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
