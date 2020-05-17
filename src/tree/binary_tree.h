#pragma once

// todo: test
class binary_tree {

public:
	struct node {
		int data{0};
		node *parent{nullptr};
		node *left{nullptr};
		node *right{nullptr};

		explicit node(int data) : data{data} {}
	};

	// 10.4-2
	static void recursive_print(node *root);

	//* 10.4-3
	static void iterate_print(node *root);

	//* 10.4-5
	static void spaceless_print(node *root);

	void insert(int data);

	node *search(int data);

	node *min(node *target);

	node *max(node *target);

	// return next bigger than target
	node *successor(node *target);

	// next smaller
	node *predecessor(node *target);

	void remove(node *target);

	void replace(node *target, node *next);

	void transplant(node *target, node *next);

	void tree_delete(node *target);

	void recursive_insert(node *target, int data);

	void rotate_left(node *target); // presume target->right exist

	void rotate_right(node *target);

	static bool is_leaf(node *target);

private:

	node *root{nullptr};
	int length{0};
};
