#ifndef ALGORITHMS_ADJACENCY_LIST_H
#define ALGORITHMS_ADJACENCY_LIST_H

#include <vector>

/* 22.1-1
 * O(n). O(mn)
 *
 *
 * */
class adjacency_list {
	public:
		adjacency_list();
		~adjacency_list();
	private:
		std::vector<int> vertices;
};


#endif //ALGOCRES_ADJACENCY_LIST_H
