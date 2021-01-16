#pragma once

class HashTable {
	// id is 1 to 26
	int *table{new int[26]{0}};

	static int hash(int data);

public:
	~HashTable() { delete[] table; }

	void insert(int data);

	bool search(int data);

	void remove(int data);
};
