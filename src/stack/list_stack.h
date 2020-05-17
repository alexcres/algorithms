#pragma once

#include "stackable.h"
#include <stdexcept>

template<typename Data=int>
class list_stack : public stackable<Data> {
	public:
		~list_stack();

		[[nodiscard]] bool is_empty() const;

		void push(const Data &data);

		Data pop();

	private:
		struct node {
			const Data &data;
			node *next;

			explicit node(const Data &data, node *next = nullptr);

			~node() { delete next; }
		};

		node *head{nullptr};
};

template<typename Data>
list_stack<Data>::node::node(const Data &data, list_stack::node *next)
	:data{data}, next{next} {}

template<typename Data>
void list_stack<Data>::push(const Data &data) {
	head = new node(data, head);
}

template<typename Data>
Data list_stack<Data>::pop() {
	if (is_empty()) {
		throw std::out_of_range("list_stack underflow");
	}
	node *temp = head->next;
	Data data = head->data;
	head->next = nullptr;
	delete head;
	head = temp;
	return data;
}

template<typename Data>
list_stack<Data>::~list_stack() {
	delete head;
}

template<typename Data>
inline bool list_stack<Data>::is_empty() const {
	return head == nullptr;
}
