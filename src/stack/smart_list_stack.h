#pragma once

#include "stackable.h"
#include <stdexcept>
#include <memory>

template<typename Data>
class smart_list_stack : public stackable<Data> {

public:
	[[nodiscard]] bool is_empty() const;

	void push(Data const &data);

	Data pop();

private:
	struct node {

		using unique_node = std::unique_ptr<node>;
		Data data;
		unique_node next;

		explicit node(Data const &data, unique_node &next = nullptr);
	};

	using unique_node = std::unique_ptr<node>;
	unique_node head;
};

template<typename Data>
smart_list_stack<Data>::node::node(const Data &data, unique_node &next)
	:data{data}, next{std::move(next)} {}

template<typename Data>
bool smart_list_stack<Data>::is_empty() const {
	return head == nullptr;
}

template<typename Data>
void smart_list_stack<Data>::push(Data const &data) {
	head = std::make_unique<node>(data, head);
}

template<typename Data>
Data smart_list_stack<Data>::pop() {
	if (is_empty()) {
		throw std::out_of_range("smart_list_stack underflow");
	}
	Data data = head->data;
	head = std::move(head->next);
	return data;
}
