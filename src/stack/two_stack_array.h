#ifndef ALGORITHMS_TWO_STACK_ARRAY_H
#define ALGORITHMS_TWO_STACK_ARRAY_H

// 10.1-2
// implement two stacks in one array
// no overflow unless both overflow
// push, pop: must be O(1) time

//v1, no resize
class two_stack_array {
public:
	explicit two_stack_array(int capacity);

	~two_stack_array();

	void push(int data, bool left_stack=true);

	int pop(bool left_stack=true);

private:
	int capacity;
	int *stack;
	int left_offset;
	int right_offset;
};

#endif //ALGORITHMS_TWO_STACK_ARRAY_H
