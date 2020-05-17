#pragma once

#include "../queue/array_queue.h"
// 10.1-7
// one queue is always empty
// the empty queue is used to drain all data instead of the last data to be popped.
class two_queue_stack {
public:
	void push(int data); // O(1)
	int pop(); // O(n)
	[[nodiscard]] int get_length() const {return length;}

private:
	array_queue queue_a;
	array_queue queue_b;
	int length;
};
