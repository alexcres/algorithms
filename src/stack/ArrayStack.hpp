#pragma once

#include <stdexcept>
#include "Stackable.hpp"
#include "../Util.hpp"

template<typename E>
class ArrayStack : public Stackable<E> {
	public:
		~ArrayStack();

		void push(E const& elem);

		E pop();

		[[nodiscard]] bool is_empty() const { return top == 0; }

		[[nodiscard]] int get_capacity() const { return capacity; } // for test

		[[nodiscard]] int get_length() const { return top; }

//	[[nodiscard]] int get_length() const { return top; }

	private:
		int top{0};
		int capacity{2};
		E* stack{new E[capacity]};

		void resize(int new_size);
};


template<typename E>
ArrayStack<E>::~ArrayStack() {
	delete[] stack;
}

template<typename E>
void ArrayStack<E>::push(E const& elem) {
	if (top >= capacity)
		resize(capacity * 2);
	stack[top++] = elem;
}

template<typename E>
E ArrayStack<E>::pop() {
	if (is_empty()) {
		throw std::out_of_range("array_stack Underflow");
	}
	// top > 1: prevent division by 0
	if (top > 1 && capacity / (top - 1) >= 4)
		resize(capacity / 2);
	return stack[--top];
}

template<typename E>
void ArrayStack<E>::resize(int new_size) {
	int* temp{new E[new_size]};
	for (int i = 0; i < top; ++i) {
		temp[i] = stack[i];
	}
	delete[] stack;
	stack = temp;
	capacity = new_size;
}
