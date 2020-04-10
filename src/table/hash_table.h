#ifndef ALGORITHMS_HASHTABLE_H
#define ALGORITHMS_HASHTABLE_H


class hash_table {
	// data is 1 to 26
	int *table{new int[26]{0}};

	static int hash(int data);

public:
	~hash_table() { delete[] table; }

	void insert(int data);

	bool search(int data);

	void remove(int data);
};


#endif //ALGORITHMS_HASHTABLE_H
