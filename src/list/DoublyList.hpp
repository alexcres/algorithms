#pragma once

// Can't use memory tool cause circular structure, no owner
// like a tree of breadth one

class DoublyList {

public:

	// must be public for find and remove node to work
	struct node {
		int data;
		node* prev{nullptr};
		node* next{nullptr};

		explicit node(int data);
	};

	// point sentinel next and prev to itself
	DoublyList();

	[[nodiscard]] node* find(int data) const; // O(n)

	void insert_head(node*& node); // O(1)

	void remove(node*& node);

	void push_head(int data);
//
//	void push_tail(int data);
//
//	int pop_head();
//
//	int pop_tail();

	int get_length() { return length; }

	node* get_head() { return sentinel->next; }

	~DoublyList();

private:
	//connect head and tail
	// head: sentinel->next
	// tail: sentinel->prev
	// sentinel remove head/tail bound checking, can improve code readability
	// sentinel adds one node overhead, don't use when lots of small lists is needed
	node* sentinel{new node(0)};
	int length{0};
};
