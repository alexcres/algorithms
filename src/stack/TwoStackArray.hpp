#pragma once

// 10.1-2
// implement two stacks in one array
// no overflow unless both overflow
// push, pop: must be O(1) time

//v1, no resize
class TwoStackArray {
public:
	explicit TwoStackArray(int capacity);

	~TwoStackArray();

	void push(int data, bool left_stack=true);

	int pop(bool left_stack=true);

private:
	int capacity;
	int *stack;
	int left_offset;
	int right_offset;
};
