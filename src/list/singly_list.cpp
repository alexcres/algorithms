#include "singly_list.h"

singly_list::node::node(int data) :
	data{data} {}
singly_list::~singly_list() {
	if (length != 0) { // head might be deleted somewhere else
		while (head) {
			auto temp = head->next;
			delete head;
			head = temp;
		}
	}
}
void singly_list::insert_head(singly_list::node *&node) {
	node->next = head;
	head = node;
	++length;
}

void singly_list::push_head(int data) {
	node *node{new struct node(data)};
	insert_head(node);
}

singly_list::node *singly_list::find(int data) const {
	auto cur = head;
	while (cur && cur->data != data) {
		cur = cur->next;
	}
	return cur;
}

// copy next data to current
// remove next
void singly_list::remove(singly_list::node *&cur) {
	auto next = cur->next;
	if (next) {
		cur->data = next->data;
		cur->next = next->next;
		delete next;
	} else {
		delete head;
		// head can still accessible in destructor, causing double free error
		// make sure don't delete it again in destructor
		// Follow the rule: one new, one delete, no more.
	}
	--length;
}

int singly_list::peek(int index) {
	auto result = head;
	for (int i = 0; i < index; ++i) {
		result = result->next;
	}
	return result->data;
}

void singly_list::reverse() {
	auto cur = head;
	auto next = head->next;
	head->next = nullptr; // remove this if circular list
	while (next) {
		auto temp = next->next;
		next->next = cur;
		cur = next;
		next = temp;
	}
	head = cur;
}









