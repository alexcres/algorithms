#include <gtest/gtest.h>
#include "../src/list/doubly_list.h"
#include "../src/list/singly_list.h"
#include "../src/list/one_ptr_doubly_list.h"


TEST(ListTest, DoublyList) {
	// only test memory leak

	doubly_list list;
	//init
	for (int i = 0; i < 8; ++i) {
		list.push_head(i + 1);
	}

	for (int i = 0; i < 8; ++i) {
		doubly_list::node *target = list.find(i + 1);
		list.remove(target);
	}
}

TEST(ListTest, SinglyList) {
	singly_list list;
	//init
	for (int i = 0; i < 4; ++i) {
		list.push_head(i + 1);
	}
	// 4->3->2->1->nullptr

	list.reverse();
	// 1->2->3->4->nullptr
	EXPECT_EQ(list.peek(), 1);

	for (int i = 0; i < 4; ++i) {
		EXPECT_EQ(list.peek(), i + 1);
		auto target = list.find(i + 1);
		list.remove(target);
	}
}

TEST(ListTest, one_ptr_doubly_list) {
// only test memory leak

	one_ptr_doubly_list list;
	//init
	for (int i = 0; i < 8; ++i) {
		list.push_head(i + 1);
	}
//	list.remove(std::pair<one_ptr_doubly_list::node*, one_ptr_doubly_list::node*>(nullptr, nullptr));

	for (int i = 0; i < 8; ++i) {
		auto target = list.find(i + 1);
		list.remove(target);
	}
}