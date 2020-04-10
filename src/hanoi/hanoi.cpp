#include <iostream>
#include "hanoi.h"
using namespace std;
int main() {
	hanoi hanoi;
	cout << "Initial game state: " << endl;
	cout << hanoi << endl;
	hanoi.solve2();
	cout << "Final game state: " << endl;
	cout << hanoi << endl;
	return 0;
}