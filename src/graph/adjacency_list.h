#pragma once

#include <vector>
#include <array>
#include <list>
#include <stack>
#include <memory>
#include <map>

using ID = int;
enum class Color {
	white, gray, black
};

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
static const int infinite = std::numeric_limits<int>::max();

struct vertex {
	int id;
//			int weight{0}; // edge weight/length
	Color color{Color::white};
	vertex *next{nullptr};
	vertex *parent{nullptr};
	int distance_to_root{infinite};
	int discover_time{0};
	int min_adjacent_time{infinite};
	int finish_time{0};

	explicit vertex(int id);
//			vertex(int id, int weight);
};

class adjacency_list {
public:
	using edge = std::array<int, 2>;
	using edges = std::vector<edge>;

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
	void visit_sub_tree(int index, edges &edges);

	void dfs();

	void stack_dfs(); // 22.3-7

	void topo_sort();

	using component = std::vector<vertex *>;
	using components = std::vector<component>;

	components get_components();

	edges get_bridges();

	void dfs_visit(int index);

	[[nodiscard]] edges get_edges() const; // for test only

private:

	int n;
	int time{0};

	// node: real vertex are in vertices
	// list only serve as link, don't read data from it
	std::vector<vertex *> vertices;
//	std::map<int, std::unique_ptr<GraphPoint>> graph_;
//		std::vector<std::unique_ptr<vertex>> vertices;

	void init(int n); // fill vertices with vertex based on indices
	void clear_list(vertex *head);

	void clear(); // free objecs in vertices
};

// 22.4-2
template<typename V>
int count_path(V *a, V *b) {
	if (a->id == b->id) {
		return 1;
	} else {
		int path = 0;
		auto next = a->next;
		while (next) {
			path += count_path(next, b);
			next = next->next;
		}
		return path;
	}
}

// Dijkstra
/* Start form a single source S, S.d = 0, S.p = null
 *
 * Visit(C):
 *
 * if no_adjacent available
 *    return C
 * smallest.d = infinite
 * for each V adjacent to C
 *    d_to_source = weight(V, C) + C.d
 *    // relaxation
 *    if d_to_source < V.d
 *       V.d = d_to_source
 *       V.p = C
 *       if smallest.d > V.d
 *          smallest = V
 * return smallest
 *
 * if C == smallest
 *    // repeat Visit(C) until all V from S are visited
 *    // can use a min_que to keep unvisited instead
 *    return;
 * C = smallest
 * mark C as visited
 */
