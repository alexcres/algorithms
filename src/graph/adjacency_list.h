#ifndef ALGORITHMS_ADJACENCY_LIST_H
#define ALGORITHMS_ADJACENCY_LIST_H

#include <vector>
#include <array>

enum color {white, gray, black};

/* 22.1-1
 * O(n). O(mn)
 *
 *
 * */
/* each number is the vertex id
 *
 * for example, to represent 1 - 0 - 2 :
 * 0 -> 1 -> 2
 * 1 -> 0
 * 2 -> 0
 *
 * p.s. arrow means nothing for un-directed graph
 * */

class adjacency_list {
		using edge = std::array<int, 2>;
		using edges = std::vector<edge>;
		static const int infinite = std::numeric_limits<int>::max();

	public:
		explicit adjacency_list(int n);
		~adjacency_list();
		void add_edge(int from, int to); // add to the end of the list
		// void add_edge(int from, int to, int weight);
		void transpose(); // reverse every edge direction
		void clean(); // 22.1-4, multi-edge to single, eliminate self-loop
		void bfs(int index);
		void print_path(int from, int to) const;
		int diameter(); // 22.2-8
		edges visit_edges(int index); // 22.2-9
		void visit_sub_tree(int index, edges& edges);
		[[nodiscard]] edges get_edges() const; // for test only

	private:
		struct vertex {
			int id;
//			int weight{0}; // edge weight/length
			color color{color::white};
			vertex* next{nullptr};
			vertex* parent{nullptr};
			int distance_to_root{infinite};
			explicit vertex(int id);
//			vertex(int id, int weight);
		};

		int n;

		// node: real vertex are in vertices
		// list only serve as link, don't read data from it
		std::vector<vertex*> vertices;
//		std::vector<std::unique_ptr<vertex>> vertices;

		void init(int n); // fill vertices with vertex based on indices
		void clear_list(vertex* head);
		void clear(); // free objecs in vertices
};

#endif //ALGOCRES_ADJACENCY_LIST_H
