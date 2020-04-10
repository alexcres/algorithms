#include "two_queue_stack.h"

void two_queue_stack::push(int data) {
	if (queue_a.is_empty()) queue_b.enqueue(data);
	else queue_a.enqueue(data);
	++length;
}

int two_queue_stack::pop() {
	int result{0};
	if (queue_a.is_empty()) {
		while (queue_b.get_length() != 1) {
			queue_a.enqueue(queue_b.dequeue());
		}
		result = queue_b.dequeue();
	} else {
		while (queue_a.get_length() != 1) {
			queue_b.enqueue(queue_a.dequeue());
		}
		result = queue_a.dequeue();
	}
	--length;
	return result;
}

