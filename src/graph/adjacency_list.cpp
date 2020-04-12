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


adjacency_list::vertex::vertex(int id) : id{id} {}

//adjacency_list::vertex::vertex(int id, int weight) : id{id}, weight{weight} {}
