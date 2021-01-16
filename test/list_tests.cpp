#include <gtest/gtest.h>
#include "../src/list/DoublyList.hpp"
#include "../src/list/SinglyList.hpp"
#include "../src/list/OnePtrDoublyList.hpp"


TEST(ListTest, DoublyList) {
	// only test memory leak

	DoublyList list;
	//init
	for (int i = 0; i < 8; ++i) {
		list.push_head(i + 1);
	}

	for (int i = 0; i < 8; ++i) {
		DoublyList::node *target = list.find(i + 1);
		list.remove(target);
	}
}

TEST(ListTest, SinglyList) {
	SinglyList list;
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

	OnePtrDoublyList list;
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