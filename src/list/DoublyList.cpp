#include "DoublyList.hpp"

DoublyList::node *DoublyList::find(int data) const {
	// eliminate result != sentinel test
	// data can always be found, hence the loop always terminate
	sentinel->data = data; // 10.2-4
	node *result = sentinel->next;
	while (result->data != data) {
		result = result->next;
	}
	return (result == sentinel) ? nullptr : result;
}

void DoublyList::insert_head(node *&node) {
	// make sure tail: sentinel->prev and possible circle: sentinel->next->next unchanged
	// link with original head
	node->next = sentinel->next;
	sentinel->next->prev = node;

	// turn the new node to head and connect to sentinel
	sentinel->next = node;
	node->prev = sentinel;

	++length;
}

void DoublyList::remove(DoublyList::node *&node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
	--length;
}

DoublyList::~DoublyList() {
	auto temp = sentinel->next;
	for (int i = 0; i < length; ++i) {
		delete sentinel;
		sentinel = temp;
		temp = sentinel->next;
	}
	delete sentinel;
}

void DoublyList::push_head(int data) {
	node *node{new struct node(data)};
	insert_head(node);
}

DoublyList::DoublyList() {
	sentinel->prev = sentinel;
	sentinel->next = sentinel;
}


//
//void doubly_list::push_tail(int data) {
//	unique_node node = std::make_shared<DoublyNode>(data);
//	tail->next = node;
//	node->prev = tail;
//	tail = node;
//	++length;
//}
//
//int doubly_list::pop_head() {
//	if (length == 0) return nullptr;
//	unique_node temp = head;
//	head = head->next;
//	head->prev = nullptr;
//	temp->next = nullptr;
//	--length;
//	return temp;
//}
//
//int doubly_list::pop_tail() {
//	if (length == 0) return nullptr;
//	unique_node temp = tail;
//	tail = tail->prev;
//	tail->next = nullptr;
//	temp->prev = nullptr;
//	--length;
//	return temp;
//}
DoublyList::node::node(int data) :
	data{data} {}

//doubly_list::node::~node() {
//	delete prev;
//	delete next;
//}

