#include "ArrayQueue.hpp"
#include <stdexcept>
void ArrayQueue::enqueue(int data) {
	if (length == capacity) resize(capacity * 2);
	queue[tail++] = data;
	if (tail == capacity) tail = 0;
	++length;
}

int ArrayQueue::dequeue() {
	if (length == 0) {
		throw std::out_of_range("array_queue Underflow");
	}
	if (shrinkable()) resize(capacity / 2);
	int result = queue[head++];
	if (head == capacity) head = 0;
	--length;
	return result;
}

void ArrayQueue::resize(int new_cap) {
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

ArrayQueue::~ArrayQueue() {
	delete[] queue;
}

bool ArrayQueue::shrinkable() {
	if (length == capacity || capacity <= 8) {
		return false;
	}
	int diff = (tail > head) ? tail - head : (capacity - head) + tail;
	return (diff <= capacity / 4);
}
