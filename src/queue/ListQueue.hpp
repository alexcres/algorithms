#pragma once

#include <memory>

class ListQueue {
public:
	void enqueue(int data);

	int dequeue();

	~ListQueue();

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
