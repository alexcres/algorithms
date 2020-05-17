#pragma once

class hash_table {
	// id is 1 to 26
	int *table{new int[26]{0}};

	static int hash(int data);

public:
	~hash_table() { delete[] table; }

	void insert(int data);

	bool search(int data);

	void remove(int data);
};
