#include "stack_memory.h"

stack_memory::stack_memory(int n) :
	capacity{n} {
	for (int i = 0; i < capacity; ++i) {
		memory.push(i + 1);
	}
}

int stack_memory::allocate() {
	if (memory.get_length() == 0)
		return 0;
	else
		return memory.pop();
}

void stack_memory::free(int obj_pointer) {
	memory.push(obj_pointer);
}

