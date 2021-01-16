#include "TwoStackQueue.hpp"

void TwoStackQueue::enqueue(int data) {
	in_stack.push(data);
	++length;
}

int TwoStackQueue::dequeue() {
	if (out_stack.is_empty()) {
		while (!in_stack.is_empty()) {
			out_stack.push(in_stack.pop());
		}
	}
	--length;
	return out_stack.pop();
}


