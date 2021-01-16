#include <iostream>
#include "Hanoi.hpp"
using namespace std;
int main() {
	Hanoi hanoi;
	cout << "Initial game state: " << endl;
	cout << hanoi << endl;
	hanoi.solve2();
	cout << "Final game state: " << endl;
	cout << hanoi << endl;
	return 0;
}