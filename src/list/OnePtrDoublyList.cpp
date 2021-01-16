#include <cstdint>
#include "OnePtrDoublyList.hpp"

using Node = OnePtrDoublyList::node;

OnePtrDoublyList::node::node(int data) :
	data{data} {}

void OnePtrDoublyList::push_head(int data) {
	node *node{new struct node(data)};
	if (length > 0) {
		head->neighbor = xor_neighbor(node, head_next);
		node->neighbor = head;
		head_next = head;
		head = node;
	} else {
		head = node;
	}
	++length;
}

std::pair<Node *, Node *> OnePtrDoublyList::find(int data) {
	auto result = head;
	auto resultNext = head_next;
	while (result && result->data != data) {
		auto temp = result;
		result = resultNext;
		if (resultNext)
			resultNext = xor_neighbor(temp, resultNext->neighbor);
	}
	return std::pair(result, resultNext);
}

Node *OnePtrDoublyList::xor_neighbor(node *&prev, node *&next) {
	return (node *) ((uintptr_t) prev ^ (uintptr_t) next);
}

void OnePtrDoublyList::remove(std::pair<node *, node *> nodes) {
	auto cur = nodes.first;
	auto next = nodes.second;

	// test needs to consider: cur, next; head, head_next
	if (cur) {
		auto prev = get_prev(nodes);

		// cur always exist
		// next relate to cur closely
		// cur doesn't have relation with head or head_next.
		// do elimination test is simpler. eliminate next first.
		if (!next) {// cur is at the end
			if (cur == head) {
				head = nullptr;
			} else if (cur == head_next) {
				head_next = nullptr;
			} else {
				auto prevPrev = get_prev(std::pair(prev, cur));
				prev->neighbor = prevPrev;
			}
		} else {
			auto nextNext = xor_neighbor(next->neighbor, cur);
			next->neighbor = xor_neighbor(prev, nextNext);
			if (prev) { // cur and next in the middle
				auto prevPrev = get_prev(std::pair(prev, cur));
				prev->neighbor = xor_neighbor(prevPrev, next);
				if (cur == head_next) head_next = next;
			} else { // cur is the head, next is the head_next
				head = next;
				head_next = nextNext;
			}
		}

		delete cur;
		--length;
	}
}

OnePtrDoublyList::~OnePtrDoublyList() {
	if (length != 0) {
		auto cur = head;
		auto next = head_next;
		while (head) {
			if (head_next)
				next = xor_neighbor(head_next->neighbor, cur);
			cur = head_next;
			delete head;
			--length;
			head = cur;
			head_next = next;
		}
	}
}
