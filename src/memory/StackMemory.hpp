#pragma once

#include "../stack/ArrayStack.hpp"

// don't need to track obj.next
class StackMemory {
public:
	explicit StackMemory(int n = 4);

	int allocate(); // pop()
	void free(int obj_pointer); // push()
private:
	ArrayStack<int> memory;
	int capacity;
};
