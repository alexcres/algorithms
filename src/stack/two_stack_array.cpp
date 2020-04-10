#include <stdexcept>
#include "two_stack_array.h"

two_stack_array::two_stack_array(int capacity) :
	capacity{capacity},
	stack{new int[capacity]},
	left_offset{0},
	right_offset{capacity} {}

two_stack_array::~two_stack_array() {
	delete[] stack;
}

void two_stack_array::push(int data, bool left_stack) {
	if (left_offset == right_offset)
		throw std::out_of_range("two_stack_array Overflow");
	if (left_stack)
		stack[left_offset++] = data;
	else
		stack[--right_offset] = data;
}

int two_stack_array::pop(bool left_stack) {
	int result{0};
	if (left_stack) {
		if (left_offset == 0)
			throw std::out_of_range("two_stack_array Left stack Underflow");
		else
			result = stack[--left_offset];
	} else {
		if (right_offset == capacity)
			throw std::out_of_range("two_stack_array Right stack Underflow");
		else
			result = stack[right_offset++];
	}
	return result;
}

