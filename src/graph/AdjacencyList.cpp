#include <queue>
#include <iostream>
#include <stack>
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"

AdjacencyList::AdjacencyList(int n) : n{n} {
	init(n);
}

AdjacencyList::~AdjacencyList() {
	clear();
}

void AdjacencyList::add_edge(int from, int to) {
	auto cur = vertices[from];
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = new vertex(to);
}

/* procedure:
 * for each edge, store its reverse in a vector
 * clear head->next
 * add each reversed edge to vertices
 *
 * performance: O(v+e), memory: O(e)
 * */
void AdjacencyList::transpose() {
	Edges reversed_edges;
	for (int i = 0; i < n; ++i) {
		auto head = vertices[i];
		auto next = head->next;
		auto hold = next;
		while (next) {
			reversed_edges.push_back({next->id, head->id});
			next = next->next;
			delete hold;
			hold = next;
		}
		head->next = nullptr;
	} // O(v+e)
	for (auto edge : reversed_edges) { // O(e)
		add_edge(edge[0], edge[1]);
	}
}


void AdjacencyList::init(int n) {
	vertices.reserve(n);
	for (int i = 0; i < n; ++i) {
		vertices.push_back(new vertex(i));
	}
}

void AdjacencyList::clear() {
	// delete list one at a time
	for (int i = 0; i < n; ++i) {
		clear_list(vertices[i]);
	}
}

void AdjacencyList::clear_list(vertex *head) {
	auto cur = head;
	auto next = cur->next;
	while (cur) {
		delete cur;
//		cur = nullptr;
		cur = next;
		if (next)
			next = next->next;
	}
//	head = nullptr;
}


AdjacencyList::Edges AdjacencyList::get_edges() const {
	Edges edges;
	for (int i = 0; i < n; ++i) {
		auto head = vertices[i];
		auto next = head->next;
		while (next) {
			edges.push_back({head->id, next->id});
			next = next->next;
		}
	}
	return edges;
}

// O(v+e), memory: v*v
// key: register exisited edges
void AdjacencyList::clean() {
	AdjacencyMatrix matrix(n);
	for (int i = 0; i < n; ++i) {
		auto head = vertices[i];
		auto cur = head;
		auto next = head->next;
		while (next) {
			if (matrix.exist(head->id, next->id) || head->id == next->id) {
				cur->next = next->next;
				delete next;
				next = cur->next;
			} else {
				matrix.add_edge(head->id, next->id);
			}
			cur = cur->next;
			if (cur)
				next = cur->next;
		}
	}
}

void AdjacencyList::bfs(int index) {
	// its important to reset, might need different index bfs
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
		v->distance_to_root = infinite;
	}
	auto root = vertices[index];
	root->color = Color::gray;
	root->distance_to_root = 0;
	std::queue<vertex *> q; // tracking grays
	q.push(root);
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		auto next = cur->next;
		while (next) {
			// cause edges are not in vertices's, should replace edges with array of ids
			auto real_next = vertices[next->id];
			if (real_next->color == Color::white) {
				real_next->color = Color::gray;
				// distance is always shortlest cause on each visit
				// the closest, which are neighbours are visited once
				// for weighted graph, change list to binary_search_tree to make sure shortest path
				real_next->distance_to_root = cur->distance_to_root + 1;
				real_next->parent = cur;
				q.push(real_next); // q.front is always in vertices
			}
			next = next->next;
		}
		cur->color = Color::black;
	}
} // O(v), only white get pushed into queue, there are v whites

void AdjacencyList::print_path(int from, int to) const {
	if (from != to) {
		auto parent = vertices[from]->parent;
		if (parent) {
			std::cout << parent->id << std::endl;
			print_path(parent->id, to);
		} else {
			std::cout << "no path from " << from << " to " << to << " exists" << std::endl;
		}
	} else {
		std::cout << "done" << std::endl;
	}
}

/* let diameter be (a,b)
 * run bfs(x), get a or b
 * run bfs(a or b), get b or a
 * */
// O(v)
int AdjacencyList::diameter() {
	bfs(0);
	int max = 0;
	int max_id = 0;
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		if (v->distance_to_root > max) {
			max = v->distance_to_root;
			max_id = v->id;
		}
	}
	bfs(max_id);
	max = 0;
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		if (v->distance_to_root > max) {
			max = v->distance_to_root;
		}
	}
	return max;
}

// draw the bfs produced tree for better understanding
void AdjacencyList::visit_sub_tree(int index, Edges &edges) {
	auto parent = vertices[index];
	auto next = parent->next;
	while (next) {
		if (parent->distance_to_root + 1 == vertices[next->id]->distance_to_root) {
			edges.push_back({parent->id, next->id});
			visit_sub_tree(next->id, edges);
		}
		next = next->next;
	}
}

AdjacencyList::Edges AdjacencyList::visit_edges(int index) {
	bfs(index);
	Edges e;
	visit_sub_tree(index, e);
	return e;
}

void AdjacencyList::dfs() {
	// reset
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
	}
	time = 0;

	for (int i = 0; i < n; ++i) {
		if (vertices[i]->color == Color::white) {
			dfs_visit(i); // if this called, a new tree is created
			// update cc(comon component) here 22.3-12
			// all sub-children of a parent have the same cc
		}
	}
}

void AdjacencyList::dfs_visit(int index) {
	auto parent = vertices[index];
	++time;
	parent->discover_time = time;
	parent->color = Color::gray;
	auto next = parent->next;
	while (next) {
		// if gray -> back edge
		// if black then:
		// if first.discover_time < second.discover_time -> forward edge
		// if first.discover_time > second.discover_time -> cross edge
		auto real_next = vertices[next->id];
		if (real_next->color == Color::white) {
			// tree edge
			real_next->parent = parent;
			dfs_visit(real_next->id); // go deeper first
		}
		next = next->next;
	}
	parent->color = Color::black;
	++time;
	parent->finish_time = time;
	// topo_sort push_front here
}

void AdjacencyList::stack_dfs() {
	// reset
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
	}
	time = 0;

	std::stack<vertex *> s;
	for (int i = 0; i < n; ++i) {
		// if black then:
		// if first.discover_time < second.discover_time -> forward edge
		// if first.discover_time > second.discover_time -> cross edge
		if (vertices[i]->color == Color::white) {
			s.push(vertices[i]);
			while (!s.empty()) {
				auto parent = s.top();
				s.pop();
				++time;
				parent->discover_time = time;
				parent->color = Color::gray;
				auto next = parent->next;
				while (next) {
					// if gray -> back edge
					auto real_next = vertices[next->id];
					if (real_next->color == Color::white) {
						real_next->parent = parent;
						s.push(real_next);
					}
					next = next->next;
				}
				parent->color = Color::black;
				++time;
				parent->finish_time = time;
			}
		}
	}
}

void AdjacencyList::topo_sort() {
	std::list<vertex *> l;

	// reset
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
	}
	time = 0;

	std::stack<vertex *> s;
	for (int i = 0; i < n; ++i) {
		// if black then:
		// if first.discover_time < second.discover_time -> forward edge
		// if first.discover_time > second.discover_time -> cross edge
		if (vertices[i]->color == Color::white) {
			s.push(vertices[i]);
			while (!s.empty()) {
				auto parent = s.top();
				s.pop();
				++time;
				parent->discover_time = time;
				parent->color = Color::gray;
				auto next = parent->next;
				while (next) {
					// if gray -> back edge
					auto real_next = vertices[next->id];
					if (real_next->color == Color::white) {
						real_next->parent = parent;
						s.push(real_next);
					}
					next = next->next;
				}
				parent->color = Color::black;
				++time;
				parent->finish_time = time;
				l.push_front(parent);
			}
		}
	}
	vertices.clear();
	vertices.reserve(n);
	for (auto v: l) {
		vertices.push_back(v);
	}
}

AdjacencyList::components AdjacencyList::get_components() {
	components cs;
	topo_sort();
	transpose();

	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
	}
	time = 0;

	std::stack<vertex *> s;
	for (int i = 0; i < n; ++i) { // vertices are topo sorted
		if (vertices[i]->color == Color::white) {
			component c;
			s.push(vertices[i]);
			while (!s.empty()) {
				auto parent = s.top();
				c.push_back(parent);
				s.pop();
				++time;
				parent->discover_time = time;
				parent->color = Color::gray;
				auto next = parent->next;
				while (next) {
					auto real_next = vertices[next->id];
					if (real_next->color == Color::white) {
						real_next->parent = parent;
						s.push(real_next);
					}
					next = next->next;
				}
				parent->color = Color::black;
				++time;
				parent->finish_time = time;
			}
			cs.push_back(c);
		}
	}

	transpose(); // back to original

	return cs;
}

AdjacencyList::Edges AdjacencyList::get_bridges() {
	Edges bridges;

	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = Color::white;
		v->parent = nullptr;
		v->min_adjacent_time = infinite;
	}
	time = 0;

	std::stack<vertex *> s;
	for (int i = 0; i < n; ++i) { // vertices are topo sorted
		if (vertices[i]->color == Color::white) {
			s.push(vertices[i]);
			while (!s.empty()) {
				auto parent = s.top();
				s.pop();
				++time;
				parent->discover_time = time;
				parent->color = Color::gray;
				auto next = parent->next;
				while (next) {
					auto real_next = vertices[next->id];
					if (real_next->color == Color::white) {
						real_next->parent = parent;
						s.push(real_next);
					} else {
						if (parent->min_adjacent_time > real_next->discover_time) {
							parent->min_adjacent_time = real_next->discover_time;
						}
					}
					next = next->next;
				}
				parent->color = Color::black;
				++time;
				parent->finish_time = time;
				next = parent->next;
				while(next) {
					// all adjacency vertices are visited
					// check each edge
					auto real_next = vertices[next->id];
					if (real_next->discover_time > parent->min_adjacent_time) {
						bridges.push_back({parent->id, real_next->id});
					}
					next = next->next;
				}
			}
		}
	}

	return bridges;
}


vertex::vertex(int id) : id{id} {}

//adjacency_list::vertex::vertex(int id, int weight) : id{id}, weight{weight} {}
