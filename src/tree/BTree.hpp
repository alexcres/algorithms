#pragma once

// it's a type of self-balanced tree: all leaves appear in the same level

// b <= number of children < 2b
// b-1 <= number of keys < 2b-1

#include <vector>

/* invariant:
 * every node has at most n children
 * a non-leaf node with k children contains k-1 keys
 * the root has at least two children if it is not a leaf node
 * every non-leaf node (except root ) has at least ceil(n/2) children
 * all leaves appear in the same level
 * */
class BTree {

	public:
		explicit BTree(unsigned b);

		~BTree();

		void insert(int key);
		// void remove(int key); // lots of cases, not worth the time and energy
	private:
		unsigned b; // degree
		struct node {
			node* parent{};
			std::vector<int> keys; // b - 1
			std::vector<node*> children; // b
			bool is_leaf{true};
		};
		node* root{new node()};

		static void clear(node* target);
};
