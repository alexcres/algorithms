#include "b_tree.h"

// insert into leaf
// if overflow, split and hoist
void b_tree::insert(int key) {
	auto cur = root;
	// find and follow branch
	while (!cur->is_leaf) {
		for (int i = 0; i < cur->keys.size(); ++i) {
			if (key < cur->keys[i]) {
				cur = cur->children[i];
				break;
			}
		}
	}

	auto keys = cur->keys;
	for (int j = 0; j < keys.size(); ++j) {
		if (key < keys[j]) {
			keys.insert(keys.begin() + j, key);
			break;
		}
	}

	// split, hoist
	while (cur->keys.size() == b) {
		keys = cur->keys;
		unsigned mid = keys.size() / 2 + 1;
		auto left = new node();
		for (unsigned i = 0; i < mid; ++i) {
			left->keys.push_back(keys[i]);
		}
		auto right = new node();
		for (unsigned i = mid; i < keys.size(); ++i) {
			right->keys.push_back(keys[i]);
		}

		unsigned pos = 0;
		auto parent = cur->parent;
		for (unsigned i = 0; i < parent->keys.size(); ++i) {
			if (keys[mid] < parent->keys[i]) {
				parent->keys.insert(parent->keys.begin() + i, keys[mid]);
				pos = i;
				break;
			}
		}

		parent->children[pos] = left;
		parent->children.insert(parent->children.begin() + pos + 1, right);

		cur = parent;
	}
}

b_tree::b_tree(unsigned b) : b{b} {

}

b_tree::~b_tree() {
	clear(root);
	delete root;
}

void b_tree::clear(b_tree::node* target) {
	if (!target->children.empty()) {
		for (auto node: target->children) {
			clear(node);
			delete node;
		}
	}
}

