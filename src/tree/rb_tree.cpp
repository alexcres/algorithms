#include "rb_tree.h"

void rb_tree::insert(rb_tree::node* target) {
	auto cur = root;
	auto prev = root->parent;
	while (cur != nil) {
		prev = cur;
		if (target->data < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}
	target->parent = prev;
	if (prev == nil)
		root = target;
	else if (target->data < prev->data)
		prev->left = target;
	else
		prev->right = target;
	target->left = nil;
	target->right = nil;
	target->color = color::red;
	fix_insert(target);
}

void rb_tree::fix_insert(rb_tree::node* target) {
	// goal: resolve color conflict and imbalance
	// fun fact: all black resolves conflict, all red resolves imbalance

	while (target->parent->color == color::red) {
		// if only change target to black, then one path has one more black
		auto parent = target->parent;
		auto gran = parent->parent;
		if (parent == gran->left) {
			auto uncle = gran->right;
			if (uncle->color == color::red) {
				// resolve color conflict
				parent->color = color::black;

				// then resolve color imbalance
				uncle->color = color::black;
				gran->color = color::red;

				// only added a red, all paths under gran are correct rb_tree
				// cause gran changed to red
				// set stage for next while loop
				target = gran;
			} else { // uncle->color is black
				// rotation: add a red node to one side, so new local root can be recolored to solve imbalance
				// while loop exits after this else case, hence two max rotation
				if (target == parent->right) {
					/* if without this whole left rotation
					 * right path will have two new nodes, gran and target, compared to left path
					 * one of them must be black
						* but will causing color imbalance
					 * after right rotation and fixed color imbalance
					 * target becomes gran's left child
					 * gran and target will both be red
					 * color conflict still hold*/

					// target and parent switch role, gran doesn't change
//					auto child = target;
					target = parent;
//					parent = child;
					rotate_left(target);
					// after left rotation, target becomes the left child of original target
					parent = target->parent;
				}
				parent->color = color::black; // resolve color conflict
				gran->color = color::red; // resolve color imbalance
				rotate_right(gran);
				/* why change color this way before rotation?
				 * before rotation, color is balanced, just one conflict
				 * after right rotation, gran will be on the right path, opposite to target
				 * change gran to red to keep color balance
				 * change parent to black to resolve color conflict*/
			}
		} else { // parent is gran->right
			auto uncle = gran->left;
			if (uncle->color == color::red) {
				parent->color = color::black;
				uncle->color = color::black;
				gran->color = color::red;
				target = gran;
			} else {
				if (target == parent->left) {
					target = parent;
					rotate_right(target);
					parent = target->parent;
				}
				parent->color = color::black;
				gran->color = color::red;
				rotate_left(gran);
			}
		}
	}
	root->color = color::black;
}


void rb_tree::remove(rb_tree::node* target) {
	auto cur = target;
	color cur_color = cur->color;
	auto next = cur;
	if (target->left == nil) {
		next = target->right;
		transplant(target, next);
	} else if (target->right == nil) {
		next = target->left;
		transplant(target, next);
	} else {
		// cur must be on target->right's left path
		cur = min(target->right);
		cur_color = cur->color;
		next = cur->right;
		if (cur->parent == target)
			// important when next is nil in fix_remove?
			next->parent = cur;
		else {
			// goal: make target as cur's parent
			// move next to cur position
			// what if cur->parent and next color is red?
			// will get fix at the end of fix_remove
			transplant(cur, next);
			cur->right = target->right;
			cur->right->parent = cur;
		}
		// goal: cur replace target
		transplant(target, cur);
		cur->left = target->left;
		cur->left->parent = cur;
		cur->color = target->color;
	}
	delete target;
	target = nullptr;
	// only cur is moved, need to check cur->color
	if (cur_color == color::black)
		fix_remove(next); // next replaced cur, fix next equals fix moved cur
}

void rb_tree::fix_remove(rb_tree::node* target) {
	// goal: add one black to target path
	// 1. through rotation
	// 2. just change it to black if it's red

	// goal: neutralize color imbalance by moving target up the tree

	// cause target path is -1 to sib, sib left and right must exist.
	// sib must have more element than target path
	// don't need to consider nil situation
	while (target != root && target->color == color::black) {
		// goal: sib path -1(target up one level, next loop), target path +1 (terminate loop)
		// 1. parent must be red before rotate, so as not to change sib black depth
		// 2. change parent to black

		auto parent = target->parent;
		if (target == parent->left) {
			auto sib = parent->right;
			// key: after every code block, there must be no conflict, old balance unchanged

			if (sib->color == color::red) {// parent must be black
				// goal: make black sib, we want to able to -1 on sib path
				// target path -1
				// keep color balance after rotate
				// target path still missing a black
				sib->color = color::black; // prepare to become new local root
				parent->color = color::red;
				rotate_left(parent); // target path gain a red =

				sib = parent->right; // update sib
				// new sib must be black, cause its parent (old sib) was red
			}

			if (sib->left->color == color::black && sib->right->color == color::black) {
				// solve target and sib path imbalance, then move target up one level
				sib->color = color::red; // sib path black -1
				target = parent; // now sub-parent are balanced, target move up one level
				// parent may reach root here, then this block means root->right -1
			} else {
				if (sib->right->color == color::black) {// left must be red
					// goal: make red sib->right, don't care its left
					// cause we want to change sib to red, and its right to black

					sib->left->color = color::black;
					sib->color = color::red;
					rotate_right(sib);
				}
				parent = target->parent; // red
				sib = parent->right; // black
				sib->color = parent->color; // black to red
				parent->color = color::black;
				sib->right->color = color::black;
				rotate_left(parent); // target path +1
				// target path are balanced, we are done, jump target to root
				// parent might be a root
				// update root after rotation
				target = root;
			}
		} else {
			auto sib = parent->left;
			if (sib->color == color::red) {
				sib->color = color::black;
				parent->color = color::red;
				rotate_right(parent);
				sib = parent->left;
			}
			if (sib->left->color == color::black && sib->right->color == color::black) {
				sib->color = color::red;
				target = parent;
			} else {
				if (sib->left->color == color::black) {
					sib->right->color = color::black;
					sib->color = color::red;
					rotate_left(sib);
				}
				parent = target->parent;
				sib = parent->left;
				sib->color = parent->color;
				parent->color = color::black;
				sib->left->color = color::black;
				rotate_right(parent);
				target = root;
			}
		}
	}
	// solve any conflict or imbalance
	target->color = color::black;
}

void rb_tree::transplant(rb_tree::node* target, rb_tree::node* next) {
	// connect up
	// connect target->parent with next
	if (target->parent == nil)
		root = next;
	else if (target == target->parent->left)
		target->parent->left = next;
	else
		target->parent->right = next;
	next->parent = target->parent;
}

void rb_tree::rotate_left(rb_tree::node* target) {
	// target becomes left child of next
	// add a node: target to new local's left path

	auto next = target->right;

	// using target's parent first, otherwise, need to create temp holder
	transplant(target, next);

	// do target "next's left" before change it to target
	target->right = next->left;
	if (next->left)
		next->left->parent = target;

	next->left = target;
	target->parent = next;
}

void rb_tree::rotate_right(rb_tree::node* target) {
	// target becomes right child of next
	auto next = target->left;
	transplant(target, next);
	target->left = next->right;
	if (next->right)
		next->right->parent = target;
	next->right = target;
	target->parent = next;
}


rb_tree::node* rb_tree::min(rb_tree::node* target) {
	while (target->left) {
		target = target->left;
	}
	return target;
}

// using spaceless traversal
rb_tree::~rb_tree() {
	destroy(root);

//	node *cur = root;
//	node *prev = cur->parent;
//	while (cur != nil) {
//		// go down
//		if (prev == cur->parent) {
//			if (cur->left) {
//				prev = cur;
//				cur = cur->left;
//			} else if (cur->right) {
//				// cur has only the right path
//				prev = cur;
//				cur = cur->right;
//			} else {
//				// going up
//				prev = cur;
//				cur = cur->parent;
//			}
//		}
//		// go up
//		if (prev->parent == cur) {
//			if (cur->right == prev) {
//				delete prev;
//				prev = nullptr;
//				// come up from right side, fully traversed
//				// keep up
//				prev = cur;
//				cur = cur->parent;
//			} else {
//				delete prev;
//				prev = nullptr;
//				// go down right path
//				prev = cur;
//				cur = cur->right;
//			}
//		}
//	}
	delete nil;
	nil = nullptr;
}

bool rb_tree::is_leaf(rb_tree::node* target) {
	return (target->left == nil) && (target->right == nil);
}

void rb_tree::destroy(rb_tree::node* root) {
	while (root && root != nil) {
		destroy(root->left);
		destroy(root->right);
		delete root;
		root = nullptr;
	}
}

rb_tree::rb_tree() {
	nil->parent = nil;
}
