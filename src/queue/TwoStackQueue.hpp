#pragma once

#include "../stack/ArrayStack.hpp"

// 10.1-6
// O(n) space
class TwoStackQueue {
public:
	void enqueue(int data); // O(1)

	int dequeue(); // 2 => O(1)

	[[nodiscard]] int get_length() const {return length;}
private:
	ArrayStack<int> in_stack;
	ArrayStack<int> out_stack;
	int length{0};
};
