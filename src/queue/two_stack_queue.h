#ifndef ALGORITHMS_TWO_STACK_QUEUE_H
#define ALGORITHMS_TWO_STACK_QUEUE_H

#include "../stack/array_stack.h"

// 10.1-6
// O(n) space
class two_stack_queue {
public:
	void enqueue(int data); // O(1)

	int dequeue(); // 2 => O(1)

	[[nodiscard]] int get_length() const {return length;}
private:
	array_stack<int> in_stack;
	array_stack<int> out_stack;
	int length{0};
};

#endif //ALGORITHMS_TWO_STACK_QUEUE_H
