#pragma once

#include "../queue/ArrayQueue.hpp"
// 10.1-7
// one queue is always empty
// the empty queue is used to drain all data instead of the last data to be popped.
class TwoQueueStack {
public:
	void push(int data); // O(1)
	int pop(); // O(n)
	[[nodiscard]] int get_length() const {return length;}

private:
	ArrayQueue queue_a;
	ArrayQueue queue_b;
	int length;
};
