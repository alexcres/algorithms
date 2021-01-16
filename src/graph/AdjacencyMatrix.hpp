#pragma once

#include <vector>
#include <array>

class AdjacencyMatrix {
		using Edge = std::array<int, 2>;
		using Edges = std::vector<Edge>;
	public:
		explicit AdjacencyMatrix(int n);
		~AdjacencyMatrix();
		void add_edge(int from, int to);
		void transpose();
		[[nodiscard]] bool exist(int from, int to) const;
		[[nodiscard]] bool has_universal_sink() const; // 22.1-6
		[[nodiscard]] bool is_universal_sink() const;
		[[nodiscard]] Edges get_edges() const; // for test only

	private:
		int n;
		int* graph;
//		std::vector<int> graph; // graph[n*row + column]
		[[nodiscard]] int get_row(int index) const;
		[[nodiscard]] int get_column(int index) const;

};
