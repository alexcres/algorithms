#pragma once

#include "Stackable.hpp"
#include <stdexcept>
#include <memory>

template<typename Data>
class SmartListStack : public Stackable<Data> {

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
SmartListStack<Data>::node::node(const Data &data, unique_node &next)
	:data{data}, next{std::move(next)} {}

template<typename Data>
bool SmartListStack<Data>::is_empty() const {
	return head == nullptr;
}

template<typename Data>
void SmartListStack<Data>::push(Data const &data) {
	head = std::make_unique<node>(data, head);
}

template<typename Data>
Data SmartListStack<Data>::pop() {
	if (is_empty()) {
		throw std::out_of_range("smart_list_stack underflow");
	}
	Data data = head->data;
	head = std::move(head->next);
	return data;
}
