#include "StackMemory.hpp"

StackMemory::StackMemory(int n) :
	capacity{n} {
	for (int i = 0; i < capacity; ++i) {
		memory.push(i + 1);
	}
}

int StackMemory::allocate() {
	if (memory.get_length() == 0)
		return 0;
	else
		return memory.pop();
}

void StackMemory::free(int obj_pointer) {
	memory.push(obj_pointer);
}

