#include "array_queue.h"
#include <stdexcept>
void array_queue::enqueue(int data) {
	if (length == capacity) resize(capacity * 2);
	queue[tail++] = data;
	if (tail == capacity) tail = 0;
	++length;
}

int array_queue::dequeue() {
	if (length == 0) {
		throw std::out_of_range("array_queue Underflow");
	}
	if (shrinkable()) resize(capacity / 2);
	int result = queue[head++];
	if (head == capacity) head = 0;
	--length;
	return result;
}

void array_queue::resize(int new_cap) {
	int *temp{new int[new_cap]};
	for (int i = 0; i != capacity; ++i) {
		temp[i] = queue[head++];
		if (head == tail) break; // full copy
		else if (head == capacity) head = 0; // head reach the end, reset head
	}
	delete[] queue;
	queue = temp;
	// update new head and tail
	head = 0;
	tail = capacity;
	capacity = new_cap;
}

array_queue::~array_queue() {
	delete[] queue;
}

bool array_queue::shrinkable() {
	if (length == capacity || capacity <= 8) {
		return false;
	}
	int diff = (tail > head) ? tail - head : (capacity - head) + tail;
	return (diff <= capacity / 4);
}
