#ifndef ALGORITHMS_ADJACENCY_MATRIX_H
#define ALGORITHMS_ADJACENCY_MATRIX_H


#include <vector>
#include <array>

class adjacency_matrix {
		using edge = std::array<int, 2>;
		using edges = std::vector<edge>;
	public:
		explicit adjacency_matrix(int n);
		~adjacency_matrix();
		void add_edge(int from, int to);
		void transpose();
		[[nodiscard]] bool exist(int from, int to) const;
		[[nodiscard]] bool has_universal_sink() const; // 22.1-6
		[[nodiscard]] bool is_universal_sink() const;
		[[nodiscard]] edges get_edges() const; // for test only

	private:
		int n;
		int* graph;
//		std::vector<int> graph; // graph[n*row + column]
		[[nodiscard]] int get_row(int index) const;
		[[nodiscard]] int get_column(int index) const;

};


#endif //ALGORITHMS_ADJACENCY_MATRIX_H
