#pragma once

// 10.3-2
// useful for hetero obj
class SingleMemory {
public:
	explicit SingleMemory(int n = 4);

	~SingleMemory();

	int allocate();

	void free(int obj_pointer);

private:
	int capacity;
	int *memory; // memory[3n] are pointers in real program
	int free_head = 1; // pointer in real program
};
