#pragma once

#include "../list/DoublyList.hpp"

// homo obj only, hetero obj will be paying too much memory.
class MultiMemory {
public:

	explicit MultiMemory(int n = 4);

	~MultiMemory();

	int allocate();

	void free(int obj_pointer);

	// 10.3-5
	void compactify(DoublyList obj_list, DoublyList free_list);


private:

	int capacity;
	int *data;
	int *next;
	int *prev;
	int free_head{1};
};
