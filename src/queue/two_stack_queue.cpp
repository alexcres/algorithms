#include "two_stack_queue.h"

void two_stack_queue::enqueue(int data) {
	in_stack.push(data);
	++length;
}

int two_stack_queue::dequeue() {
	if (out_stack.is_empty()) {
		while (!in_stack.is_empty()) {
			out_stack.push(in_stack.pop());
		}
	}
	--length;
	return out_stack.pop();
}


