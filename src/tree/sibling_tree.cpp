#include <iostream>
#include "sibling_tree.h"

void sibling_tree::print_data(sibling_tree::node *root) {
	if (root) {
		print_data(root->left);
		std::cout << root->data << std::endl;
		print_data(root->next);
	}
}
