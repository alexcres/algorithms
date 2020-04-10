#include <queue/list_queue.h>
list_queue::node::node(int data)
	: data{data}, next{nullptr} {}

list_queue::node::~node() {
	delete next;
}

list_queue::~list_queue() {
	delete head;
}

void list_queue::enqueue(int data) {
	node *new_node = new node(data);
	switch (length) {
		case 0:
			head = new_node;
			break;
		case 1: // connect head and tail
			tail = new_node;
			head->next = tail;
			break;
		default:
			tail->next = new_node;
			tail = tail->next;
	}
	++length;
}

int list_queue::dequeue() {
	if (length == 0) {
		throw std::out_of_range("list_queue Underflow");
	}
	int result = head->data;
	node *temp = head->next;
	head->next = nullptr;
	delete head;
	head = temp;
	--length;
	return result;
}
