#include <gtest/gtest.h>
#include "../src/tree/binary_tree.h"
#include "../src/tree/rb_tree.h"
#include "../src/tree/b_tree.h"


TEST(TreeTest, BinaryTree) {
	binary_tree tree;
}

TEST(TreeTest, rb_tree) {
	rb_tree tree;
	for (int i = 1; i < 5; ++i) {
		auto node = new rb_tree::node(i);
		tree.insert(node);
	}
}

TEST(TreeTest, b_tree) {
	b_tree tree{5};
	for (int i = 0; i < 100; ++i) {
		tree.insert(i+1);
	}
}