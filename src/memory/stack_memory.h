#ifndef ALGORITHMS_STACK_MEMORY_H
#define ALGORITHMS_STACK_MEMORY_H


#include "../stack/array_stack.h"

// don't need to track obj.next
class stack_memory {
public:
	explicit stack_memory(int n = 4);

	int allocate(); // pop()
	void free(int obj_pointer); // push()
private:
	array_stack<int> memory;
	int capacity;
};


#endif //ALGORITHMS_STACK_MEMORY_H
