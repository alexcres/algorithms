#include <iostream>
#include "SiblingTree.hpp"

void SiblingTree::print_data(SiblingTree::node *root) {
	if (root) {
		print_data(root->left);
		std::cout << root->data << std::endl;
		print_data(root->next);
	}
}
