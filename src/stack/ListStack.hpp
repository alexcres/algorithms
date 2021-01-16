#pragma once

#include "Stackable.hpp"
#include <stdexcept>

template<typename Data=int>
class ListStack : public Stackable<Data> {
	public:
		~ListStack();

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
ListStack<Data>::node::node(const Data &data, ListStack::node *next)
	:data{data}, next{next} {}

template<typename Data>
void ListStack<Data>::push(const Data &data) {
	head = new node(data, head);
}

template<typename Data>
Data ListStack<Data>::pop() {
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
ListStack<Data>::~ListStack() {
	delete head;
}

template<typename Data>
inline bool ListStack<Data>::is_empty() const {
	return head == nullptr;
}
