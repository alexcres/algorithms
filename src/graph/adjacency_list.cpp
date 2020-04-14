#include <queue>
#include <iostream>
#include "adjacency_list.h"
#include "adjacency_matrix.h"

adjacency_list::adjacency_list(int n) : n{n} {
	init(n);
}

adjacency_list::~adjacency_list() {
	clear();
}

void adjacency_list::add_edge(int from, int to) {
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
void adjacency_list::transpose() {
	edges reversed_edges;
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


void adjacency_list::init(int n) {
	vertices.reserve(n);
	for (int i = 0; i < n; ++i) {
		vertices.push_back(new vertex(i));
	}
}

void adjacency_list::clear() {
	// delete list one at a time
	for (int i = 0; i < n; ++i) {
		clear_list(vertices[i]);
	}
}

void adjacency_list::clear_list(adjacency_list::vertex* head) {
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


adjacency_list::edges adjacency_list::get_edges() const {
	edges edges;
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
void adjacency_list::clean() {
	adjacency_matrix matrix(n);
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

void adjacency_list::bfs(int index) {
	// its important to reset, might need different index bfs
	for (int i = 0; i < n; ++i) {
		auto v = vertices[i];
		v->color = color::white;
		v->parent = nullptr;
		v->distance_to_root = infinite;
	}
	auto root = vertices[index];
	root->distance_to_root = 0;
	std::queue<vertex*> q;
	q.push(root);
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		auto next = cur->next;
		while(next) {
			auto real_next = vertices[next->id];
			if (real_next->color == color::white) {
				real_next->color = color::gray;
				// distance is always shortlest cause on each visit
				// the cloest, which are neighbours are visited once
				// for weighted graph, change list to binary_search_tree to make sure shortest path
				real_next->distance_to_root = cur->distance_to_root + 1;
				real_next->parent = cur;
				q.push(real_next); // q.front is always in vertices
			}
			next = next->next;
		}
		cur->color = color::black;
	}
} // O(v), only white get pushed into queue, there are v whites

void adjacency_list::print_path(int from, int to) const {
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
int adjacency_list::diameter() {
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
void adjacency_list::visit_sub_tree(int index, edges& edges) {
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

adjacency_list::edges adjacency_list::visit_edges(int index) {
	bfs(index);
	edges e;
	visit_sub_tree(index, e);
	return e;
}


adjacency_list::vertex::vertex(int id) : id{id} {}

//adjacency_list::vertex::vertex(int id, int weight) : id{id}, weight{weight} {}
