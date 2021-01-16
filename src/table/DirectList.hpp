#pragma once

#include <vector>
#include <list/DoublyList.hpp>
// 11.1-3
class DirectList {
public:
	void insert(int index);

	bool search(int index);

	void remove(int index);

private:
	std::vector<DoublyList::node *> table;
};
