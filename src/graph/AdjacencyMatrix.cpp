#include "AdjacencyMatrix.hpp"

AdjacencyMatrix::AdjacencyMatrix(int n) : n{n}, graph{new int[n * n]{0}} {
//	graph = new int[n*n];
//	graph.reserve(n*n);

}

AdjacencyMatrix::~AdjacencyMatrix() {
	delete[] graph;
}

void AdjacencyMatrix::add_edge(int from, int to) {
	graph[from * n + to] = 1; // 1 can be other number to indicate weight
}

// O(n*n)
// switch row and column
void AdjacencyMatrix::transpose() {
	int* temp_graph = new int[n * n]{0};
	for (int i = 0; i < n * n; ++i) {
		if (graph[i] != 0)
			temp_graph[get_column(i) * n + get_row(i)] = graph[i];
	}
	delete[] graph;
	graph = temp_graph;
}

AdjacencyMatrix::Edges AdjacencyMatrix::get_edges() const {
	Edges edges;
	for (int i = 0; i < n * n; ++i) {
		if (graph[i] != 0) {
			edges.push_back({get_row(i), get_column(i)});
		}
	}
	return edges;
}


int AdjacencyMatrix::get_row(int index) const {
	return index / n;
}

int AdjacencyMatrix::get_column(int index) const {
	return index % n;
}


bool AdjacencyMatrix::exist(int from, int to) const {
	return graph[from * n + to] != 0;
}

/* two events need to be true for the universal sink vertex:
 * 1. the row is all zero
 * 2. the column is all one except on its row
**/

bool AdjacencyMatrix::has_universal_sink() const {
	bool has_sink = false;
	for (int row = 0; row < n; ++row) {
		bool has_out = false;
		for (int column = 0; column < n; ++column) {// check the row
			if (exist(row, column)) {
				has_out = true;
				break;
			}
		} // O(v)
		if (!has_out) { // check columns
			int column = row;
			int all_in = true;
			for (int i = 0; i < n; ++i) {
				if (i != row && !exist(i, column)) {
					all_in = false;
					break;
				}
			}// O(v)
			if (all_in) {
				has_sink = true;
				break;
			}
		}
	} // O(v)
	return has_sink;
} // O(v*v)

/* hidden:
 * there can only be one sink
 *
 * procedure:
 * row=column=0
 * while row < v and column < v:
 *    if edge_exist(row, column):
 *       ++row
 *    else
 *       ++column
 * check if v = row is the universal sink
 */

// if 0 continue the row, if 1 pipe to next row
// sink can't exist after thw sink row, cause there can't be more than one 0 in the same column
bool AdjacencyMatrix::is_universal_sink() const {
	int row = 0;
	int column = 0;
	while (row < n && column < n) {
		if (exist(row, column))
			++row;
		else
			++column;
	} // O(v)

	// check if v = row is the universal sink
	bool is_sink = true;
	for (int i = 0; i < n; ++i) {
		if (exist(row, i) || (i != row && !exist(i, row))) {
			is_sink = false;
			break;
		}
	} // O(v)
	return is_sink;
} // O(v)
