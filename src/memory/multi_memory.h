#pragma once

#include "../list/doubly_list.h"

// homo obj only, hetero obj will be paying too much memory.
class multi_memory {
public:

	explicit multi_memory(int n = 4);

	~multi_memory();

	int allocate();

	void free(int obj_pointer);

	// 10.3-5
	void compactify(doubly_list obj_list, doubly_list free_list);


private:

	int capacity;
	int *data;
	int *next;
	int *prev;
	int free_head{1};
};
