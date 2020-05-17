#pragma once

// 10.3-2
// useful for hetero obj
class single_memory {
public:
	explicit single_memory(int n = 4);

	~single_memory();

	int allocate();

	void free(int obj_pointer);

private:
	int capacity;
	int *memory; // memory[3n] are pointers in real program
	int free_head = 1; // pointer in real program
};
