#include "multi_memory.h"

multi_memory::multi_memory(int n) :
	capacity{n + 1},
	data{new int[capacity]},
	next{new int[capacity]},
	prev{new int[capacity]} {

	for (int i = 1; i < capacity; ++i) {
		next[i] = i + 1;
		prev[i] = i - 1;
	}
	next[capacity - 1] = 0;
}

multi_memory::~multi_memory() {
	delete[] data;
	delete[] prev;
	delete[] next;
}

int multi_memory::allocate() {
	if (free_head == 0) {
		return 0;
	} else {
		int objPointer = free_head;
		free_head = next[free_head];
		return objPointer;
	}
}

void multi_memory::free(int obj_pointer) {
	next[obj_pointer] = free_head;
	free_head = obj_pointer;
}

// obj length: 1...n, free length: n+1...m
void multi_memory::compactify(doubly_list obj_list, doubly_list free_list) {
	// presume capacity is m + 1
	auto curHead = obj_list.get_head();
	auto curNext = obj_list.get_head()->next;
	int objL = obj_list.get_length();
	// copy obj to 1...n
	int i = 1;
	int l = objL;
	while (i < l) {
		data[i] = curHead->data;
		next[i] = i + 1;
		prev[i] = i - 1;
		curHead = curNext;
		curNext = curNext->next;
		++i;
	}
	// last obj.next needs to point to 0
	data[i] = curHead->data;
	next[i] = 0;
	prev[i] = i - 1;
	++i;
	free_head = i; // update head
	l = objL + free_list.get_length();
	// ignore next and data
	while (i < l) {
		next[i] = i + 1;
		++i;
	}
	next[i] = 0;
}
