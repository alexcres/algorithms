#include "DirectList.hpp"

void DirectList::insert(int index) {
	auto *node = new DoublyList::node(index);
	node->next = table[index+1];
	node->prev = table[index-1];
	table[index] = node;
}

bool DirectList::search(int index) {
	return table[index];
}

void DirectList::remove(int index) {
	table[index+1]->prev = nullptr;
	table[index-1]->next = nullptr;
	table[index] = nullptr;
}
