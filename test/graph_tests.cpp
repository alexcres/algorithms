#include <gtest/gtest.h>
#include <graph/AdjacencyMatrix.hpp>
#include "../src/graph/AdjacencyList.hpp"

// figure 22.2, 0-5 instead of 1-6
TEST(graph_test, adjacency_list_test) {
	AdjacencyList graph(6);
	graph.add_edge(0, 1);
	graph.add_edge(0, 3);
	graph.add_edge(1, 4);
	graph.add_edge(2, 5);
	graph.add_edge(2, 5);
	graph.add_edge(3, 1);
	graph.add_edge(4, 3);
	graph.add_edge(5, 5);
	auto edges = graph.get_edges();
	graph.transpose();
	auto edges_trans = graph.get_edges();

	bool found = false;
	// to test if each edge is reversed
	for(auto edge: edges) {
		found = false;
		for(auto edge_trans: edges_trans) {
			if (edge[0] == edge_trans[1] && edge[1] == edge_trans[0]) {
				found = true;
				break;
			}
		}
		EXPECT_EQ(found, true);
	}
}


TEST(graph_test, adjacency_matrix_test) {
	AdjacencyMatrix graph(6);
	graph.add_edge(0, 1);
	graph.add_edge(0, 3);
	graph.add_edge(1, 4);
	graph.add_edge(2, 5);
	graph.add_edge(2, 5);
	graph.add_edge(3, 1);
	graph.add_edge(4, 3);
	graph.add_edge(5, 5);
	auto edges = graph.get_edges();
	graph.transpose();
	auto edges_trans = graph.get_edges();

	bool found = false;
	// to test if each edge is reversed
	for(auto edge: edges) {
		found = false;
		for(auto edge_trans: edges_trans) {
			if (edge[0] == edge_trans[1] && edge[1] == edge_trans[0]) {
				found = true;
				break;
			}
		}
		EXPECT_EQ(found, true);
	}

}