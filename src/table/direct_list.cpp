#include "direct_list.h"

void direct_list::insert(int index) {
	auto *node = new doubly_list::node(index);
	node->next = table[index+1];
	node->prev = table[index-1];
	table[index] = node;
}

bool direct_list::search(int index) {
	return table[index];
}

void direct_list::remove(int index) {
	table[index+1]->prev = nullptr;
	table[index-1]->next = nullptr;
	table[index] = nullptr;
}
