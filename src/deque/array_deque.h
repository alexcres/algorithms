#pragma once

#include <memory>
// 10.1-5
// all operations must be O(1)
// its similar to two_stack_array, but can go circle
class array_deque {
public:

	void push_head(int data);

	void push_tail(int data);

	int pop_head();

	int pop_tail();

	int get_length() { return length; }

	~array_deque();

private:
	int capacity{4};
	int *deque{new int[capacity]};
//	std::unique_ptr<int[]> deque{std::make_unique<int[]>(capacity)};
	int head{0};
	int tail{capacity};
	int length{0};

	void resize(int newCap);
};
