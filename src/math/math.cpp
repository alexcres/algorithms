#include "math.h"

// gcd should divided a, b and any remainders
int math::gcd(int a, int b) {
	int remainder = 0;
	do {
		remainder = a % b;
		a = b;
		b = remainder;
	} while (remainder != 0);
	return a;
}

int math::lcd(int a, int b) {
	// division first to avoid overflow
	return (a / gcd(a, b)) * b;
}
