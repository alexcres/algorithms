#ifndef ALGORITHMS_BIT_VECTOR_H
#define ALGORITHMS_BIT_VECTOR_H

#include <bitset>

// 11.1-2
class bit_vector {
public:
	void insert(int index);

	bool search(int index);

	void remove(int index);

private:
	std::bitset<100> bits;
};

#endif //ALGORITHMS_BIT_VECTOR_H
