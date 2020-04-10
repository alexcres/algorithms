#include "bit_vector.h"

void bit_vector::insert(int index) {
	bits[index] = true;
}

bool bit_vector::search(int index) {
	return bits[index];
}

void bit_vector::remove(int index) {
	bits[index] = false;
}
