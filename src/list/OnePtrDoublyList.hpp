#pragma once

#include <utility>

// 10.2-8
// for simplicity, it's better for head/tail only operation

class OnePtrDoublyList {
public:
	struct node {
		int data;
		node *neighbor{nullptr};

		explicit node(int data);
	};

	~OnePtrDoublyList();

	void push_head(int data);

	std::pair<node *, node *> find(int data);

	void remove(std::pair<node*, node*> nodes);


private:
	node *head{nullptr};
	node *head_next{nullptr};
	int length{0};

	static node *xor_neighbor(node *&prev, node *&next);

	static node* get_prev(std::pair<node*, node*> nodes) {
		return xor_neighbor(nodes.first->neighbor, nodes.second);
	}
};
