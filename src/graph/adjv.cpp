#include "adjv.h"

void graph_point::add_edge(ID id, int weight) {
	adj.emplace_back(std::make_unique<edge_point>(id, weight));
}

edge_point::edge_point(ID id, int weight): id{id}, weight{weight} {}

void graph::add(ID id) {
	graph_[id] = std::make_unique<graph_point>();
}

void graph::add_edge(ID from, ID to, int weight) {
	graph_[from]->add_edge(to, weight);
}
