#include "BitVector.hpp"

void BitVector::insert(int index) {
	bits[index] = true;
}

bool BitVector::search(int index) {
	return bits[index];
}

void BitVector::remove(int index) {
	bits[index] = false;
}
