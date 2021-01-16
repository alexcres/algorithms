#include "BinaryTree.hpp"
#include <iostream>
#include <stack>

void BinaryTree::recursive_print(BinaryTree::node *root) {
	if (root) {
		recursive_print(root->left);
		std::cout << root->data << std::endl;
		recursive_print(root->right);
	}
}

void BinaryTree::iterate_print(BinaryTree::node *root) {
	// left -> root -> right
	std::stack<BinaryTree::node *> stack;
	stack.push(root);
	while (!stack.empty()) {
		auto cur = stack.top();
		while (cur) {
			stack.push(cur->left);
			cur = stack.top();
		}
		stack.pop(); // pop nullptr
		if (!stack.empty()) {
			cur = stack.top();
			stack.pop();
			std::cout << cur->data << std::endl;
			stack.push(cur->right);
		}
	}
}

/* 1. go down left path
 * 2. go right if no left
 * 3. go up if no way
 * 4. keep go up only if fully done (right exist or on the right path)
 * 5. else go down right
 */
// left -> right -> root
void BinaryTree::spaceless_print(BinaryTree::node *root) {
	node *cur = root;
	node *prev = cur->parent;
	while (cur != nullptr) {
		// go down
		if (prev == cur->parent) {
			if (cur->left) {
				prev = cur;
				cur = cur->left;
			} else if (cur->right) {
				// cur has only the right path
				prev = cur;
				cur = cur->right;
			} else {
				// going up
				prev = cur;
				cur = cur->parent;
			}
		}
		// go up
		if (prev->parent == cur) {
			// once up, never down here again, so good to print
			std::cout << prev->data << std::endl;
			if (!cur->right || cur->right == prev) {
				// come up from right side, fully traversed
				// keep up
				prev = cur;
				cur = cur->parent;
			} else {
				// go down right path
				prev = cur;
				cur = cur->right;
			}
		}
	}
}

void BinaryTree::insert(int data) {
	if (length == 0) {
		root = new node(data);
	} else {
		auto cur = root;
		auto prev = cur->parent;
		while (cur) {
			prev = cur;
			if (data < cur->data) {
				cur = cur->left;
			} else {
				cur = cur->right;
			}
		}
		cur = new node(data);
		cur->parent = prev;
		if (data < prev->data) {
			prev->left = cur;
		} else {
			prev->right = cur;
		}
	}
	++length;
}

BinaryTree::node *BinaryTree::search(int data) {
	auto cur = root;
	while (cur) {
		if (data == cur->data) {
			break;
		}
		if (data < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return cur;
}

void BinaryTree::remove(node *target) {
	if (length == 0 || !target) return;
	if (length == 1) {
		if (target == root)
			root = nullptr;
		else
			return;
	} else {
		if (!target->left && !target->right) {
			// target is a children leaf
			if (target->parent->right == target) {
				target->parent->right = nullptr;
			} else {
				target->parent->left = nullptr;
			}
		} else if (target->right) {
			// target has right path
			auto next = successor(target);
			if (next->parent == target) { // next is target->right
				next->parent = target->parent;
				next->left = target->left;
			} else {
				if (next->right) {// next only has right branch
					// move next's right branch into the next location
					next->parent->left = next->right;
					next->right->parent = next->parent;
				}
				// move next to target location
				next->parent = target->parent;
				next->right = target->right;
				next->right->parent = next;
				next->left = target->left;
				next->left->parent = next;

				// connect target's parent to next
				replace(target, next);
			}
		} else {
			// has left path only
			// just move target's left to target
			auto next = target->left;
			replace(target, next);
			next->parent = target->parent;
		}
	}
	delete target;
	--length;
}

void BinaryTree::replace(BinaryTree::node *target, BinaryTree::node *next) {
	if (target->parent) {// not root
		if (target->parent->left == target) {
			target->parent->left = next;
		} else {
			target->parent->right = next;
		}
	} else {
		root = next;
	}
}


BinaryTree::node *BinaryTree::min(BinaryTree::node *target) {
//	return target->left ? min(target->left) : target;
	while (target->left) {
		target = target->left;
	}
	return target;
}

BinaryTree::node *BinaryTree::max(BinaryTree::node *target) {
//	return target->right ? max(target->right) : target;
	while (target->right) {
		target = target->right;
	}
	return target;
}

BinaryTree::node *BinaryTree::successor(BinaryTree::node *target) {
	if (target->right) {
		return min(target->right);
	} else {
		auto prev = target->parent;
		while (prev && target == prev->right) {
			target = prev;
			prev = prev->parent;
		}
		return prev; // prev can be nullptr when reach root->parent
	}
}

BinaryTree::node *BinaryTree::predecessor(BinaryTree::node *target) {
	if (target->left) {
		return max(target->left);
	} else {
		auto prev = target->parent;
		while (prev && target == prev->left) {
			target = prev;
			prev = prev->parent;
		}
		return prev;
	}
}

void BinaryTree::transplant(BinaryTree::node *target, BinaryTree::node *next) {
	// connect up
	// connect target->parent with next
	if (!target->parent)
		root = next;
	else if (target == target->parent->left)
		target->parent->left = next;
	else
		target->parent->right = next;
	if (next)
		next->parent = target->parent;
}

// key: do elimination test
void BinaryTree::tree_delete(BinaryTree::node *target) {
	if (!target->left)
		transplant(target, target->right);
	else if (!target->right)
		transplant(target, target->left);
	else {
		// target is full
		auto next = min(target->right);
		if (next->parent != target) {
			// next not connected to target
			transplant(next, next->right);
			next->right = target->right;
			next->right->parent = next;
		}
		transplant(target, next);
		next->left = target->left;
		next->left->parent = next;
	}
	delete target;
	--length;
}

void BinaryTree::recursive_insert(BinaryTree::node *target, int data) {
	if (!target) {
		root = new node(data);
	} else {
		if (data < target->data) {
			if (target->left)
				recursive_insert(target->left, data);
			else {
				auto node = new struct node(data);
				target->left = node;
				node->parent = target;
			}
		} else {
			if (target->right)
				recursive_insert(target->right, data);
			else {
				auto node = new struct node(data);
				target->right = node;
				node->parent = target;
			}
		}
	}
	++length;
}

void BinaryTree::rotate_left(BinaryTree::node *target) {
	auto next = target->right;

	// using target's parent first, otherwise, need to create temp holder
	transplant(target, next);

	// do node "next's left" before change it to target
	target->right = next->left;
	if (next->left)
		next->left->parent = target;

	next->left = target;
	target->parent = next;
}

void BinaryTree::rotate_right(BinaryTree::node *target) {
	auto next = target->left;
	transplant(target, next);
	target->left = next->right;
	if (next->right)
		next->right->parent = target;
	next->right = target;
	target->parent = next;
}

bool BinaryTree::is_leaf(BinaryTree::node *target) {
	return (target->right == nullptr && target->left == nullptr);
}
