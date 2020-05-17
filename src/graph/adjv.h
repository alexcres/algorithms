#pragma once

#include <vector>
#include <memory>
#include <map>
#include <list>

using ID = int;
enum class Color {
	white, gray, black
};

struct edge_point {
	explicit edge_point(ID id, int weight = 0);

	ID id;
	int weight{0};
//	std::unique_ptr<EdgePoint> next{nullptr};
};

struct graph_point {
//	using AdjancentPoints = std::vector<std::unique_ptr<EdgePoint>>;
//	AdjancentPoints adj;
//	std::unique_ptr<EdgePoint> next{nullptr};
	std::list<std::unique_ptr<edge_point>> adj;
	Color color{Color::white};
	int d_time{0};
	int f_time{0};

	void add_edge(ID id, int weight = 0);
};

class graph {
public:
	void add(ID id);

	void add_edge(ID from, ID to, int weight = 0);

private:
	// if key is string, transfer to int based on char code first
	std::map<int, std::unique_ptr<graph_point>> graph_;
};
