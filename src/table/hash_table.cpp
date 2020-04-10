#include "hash_table.h"

// universal hash
int hash_table::hash(int data) {
	// ((a*data + b)%p)%slots
	// a and b, need to be less than p to make sure relative prime to p
	// b needs to be bigger than 0, to make sure result is prime before %p
	//      randomize index for data
	//      make sure data is prime to 29
	// data could be n*29
	return ((28 * data + 1) % 29) % 26;
	// ------randomize---
}

void hash_table::insert(int data) {
	int index = hash(data);
	while (table[index] != 0) {
		++index;
	}
	table[index] = data;
}

bool hash_table::search(int data) {
	int index = hash(data);
	bool result = false;
	while (table[index] != 0) {
		if (table[index] == data) {
			result = true;
			break;
		}
		++index;
	}
	return result;
}

void hash_table::remove(int data) {
	int index = hash(data);
	while (table[index] != 0) {
		if (table[index] == data) {
			table[index] = 0;
			break;
		}
		++index;
	}
}
