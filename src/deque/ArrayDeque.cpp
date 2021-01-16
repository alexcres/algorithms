#include <stdexcept>
#include "ArrayDeque.hpp"

void ArrayDeque::push_head(int data) {
	if (head == tail) resize(capacity * 2);
	if (head == capacity) head = 0;
	deque[head++] = data;
	++length;
}

void ArrayDeque::push_tail(int data) {
	if (tail == head) resize(capacity * 2);
	if (tail == 0) tail = capacity;
	deque[--tail] = data;
	++length;
}

int ArrayDeque::pop_head() {
	if (head == 0) {
		if (tail == capacity)
			throw std::out_of_range("array_deque Underflow");
		else
			head = capacity;
	}
	--length;
	int result = deque[--head];
	if (length >= 4 && length <= capacity / 4) resize(capacity / 2);
	return result;
}

int ArrayDeque::pop_tail() {
	if (tail == capacity) {
		if (head == 0)
			throw std::out_of_range("array_deque Underflow");
		else
			tail = 0;
	}
	--length;
	int result = deque[tail++];
	if (length >= 4 && length <= capacity / 4) resize(capacity / 2);
	return result;
}

// pop_tail -> head
void ArrayDeque::resize(int newCap) {
	int *temp{new int[newCap]};
	for (int i = 0; i < length; ++i) {
		if (tail == capacity) tail = 0;
		temp[i] = deque[tail++];
	}
	delete[] deque;
	deque = temp;
	head = length;
	tail = 0;
	capacity = newCap;
}

ArrayDeque::~ArrayDeque() {
	delete[] deque;
}
