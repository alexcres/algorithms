#include "adjv.hpp"

void GraphPoint::add_edge(ID id, int weight) {
	adj.emplace_back(std::make_unique<EdgePoint>(id, weight));
}

EdgePoint::EdgePoint(ID id, int weight): id{id}, weight{weight} {}

void graph::add(ID id) {
	graph_[id] = std::make_unique<GraphPoint>();
}

void graph::add_edge(ID from, ID to, int weight) {
	graph_[from]->add_edge(to, weight);
}
