#include <gtest/gtest.h>
#include "../src/tree/BinaryTree.hpp"
#include "../src/tree/RBTree.hpp"
#include "../src/tree/BTree.hpp"


TEST(TreeTest, BinaryTree) {
	BinaryTree tree;
}

TEST(TreeTest, rb_tree) {
	RBTree tree;
	for (int i = 1; i < 5; ++i) {
		auto node = new RBTree::node(i);
		tree.insert(node);
	}
}

TEST(TreeTest, b_tree) {
	BTree tree{5};
	for (int i = 0; i < 100; ++i) {
		tree.insert(i+1);
	}
}