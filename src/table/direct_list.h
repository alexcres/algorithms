#pragma once

#include <vector>
#include <list/doubly_list.h>
// 11.1-3
class direct_list {
public:
	void insert(int index);

	bool search(int index);

	void remove(int index);

private:
	std::vector<doubly_list::node *> table;
};
