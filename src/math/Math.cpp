#include "Math.hpp"

// gcd should divided a, b and any remainders
int Math::gcd(int a, int b) {
	int remainder = 0;
	do {
		remainder = a % b;
		a = b;
		b = remainder;
	} while (remainder != 0);
	return a;
}

int Math::lcd(int a, int b) {
	// division first to avoid overflow
	return (a / gcd(a, b)) * b;
}
