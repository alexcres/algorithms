#pragma once

#include <memory>

class list_queue {
public:
	void enqueue(int data);

	int dequeue();

	~list_queue();

private:
	struct node {
		int data;
		node *next;

		explicit node(int data);

		~node();
	};

	node *head{nullptr};
	node *tail{nullptr};
	int length{0};
};
