#ifndef ALGORITHMS_SIBLING_TREE_H
#define ALGORITHMS_SIBLING_TREE_H


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


#endif //ALGORITHMS_SIBLING_TREE_H
