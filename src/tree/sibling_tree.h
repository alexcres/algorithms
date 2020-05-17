#pragma once

class sibling_tree {
public:
	struct node {
		int data{0};
		node *parent{nullptr};
		node *left{nullptr};
		node *next{nullptr};
	};

	// 10.4-4
	static void print_data(node *root);

private:
	node *root;
};
