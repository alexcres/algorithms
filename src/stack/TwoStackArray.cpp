#include <stdexcept>
#include "TwoStackArray.hpp"

TwoStackArray::TwoStackArray(int capacity) :
	capacity{capacity},
	stack{new int[capacity]},
	left_offset{0},
	right_offset{capacity} {}

TwoStackArray::~TwoStackArray() {
	delete[] stack;
}

void TwoStackArray::push(int data, bool left_stack) {
	if (left_offset == right_offset)
		throw std::out_of_range("two_stack_array Overflow");
	if (left_stack)
		stack[left_offset++] = data;
	else
		stack[--right_offset] = data;
}

int TwoStackArray::pop(bool left_stack) {
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

