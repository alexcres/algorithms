#pragma once

// todo: test
/* Properties that must hold
 * 1. Every node is either red or black
 * 2. The root is black
 * 3. Every leaf(nil) is black
 * 4. Red node's children are both black
 * 5. For each node, all path to descendant leaves has the same number of black nodes
 */
class RBTree {
		enum class color { red, black };
	public:
		struct node {
			int data{0};
			enum color color{color::red};
			node* parent{nullptr};
			node* left{nullptr};
			node* right{nullptr};

			explicit node(int data, enum color color = color::red) : data{data}, color{color} {}
//		~node() {delete }
		};

		RBTree();

		~RBTree();

		void insert(node* target);

		void remove(node* target);

		void rotate_left(node* target); // presume target->right exist

		void rotate_right(node* target);

		void transplant(node* target, node* next);

		node* min(node* target);

		bool is_leaf(node* target);


	private:
		void destroy(node* root);

		void fix_insert(node* target);

		void fix_remove(node* target);

		node* nil{new node(0, color::black)};
		node* root{nil};
};
