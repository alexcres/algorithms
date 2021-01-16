#include "SingleMemory.hpp"

SingleMemory::SingleMemory(int n) :
	capacity{3 * n + 1}, memory{new int[capacity]} {
	// fill each obj.next and obj.prev
	// next and prev are used to connect objects together
	// next is used to store free pointer when the obj is freed.
	for (int i = 2, l = capacity - 4; i < l; i += 3) {
		memory[i] = i + 2; // next
		memory[i + 1] = i + 3; // prev
	}
	memory[capacity - 2] = 0; // last obj.next
	memory[capacity - 1] = capacity - 4; // last obj.prev
}

SingleMemory::~SingleMemory() {
	delete[] memory;
}

int SingleMemory::allocate() {
	if (free_head == 0) { //! free nullptr does nothing
		return 0;
	} else {
		int objPointer = free_head;
		free_head = memory[free_head + 1];
		return objPointer;
	}
}

void SingleMemory::free(int obj_pointer) {
	//! this is why double free is bad
	// next point to free_head itself
	// when next time allocate called, it will stay being free forever.
	memory[obj_pointer + 1] = free_head; // set obj.next to free_head
	free_head = obj_pointer; //! obj doesn't change when freed, only set its pointer to free_head
	//! obj is still point to the same value
}
