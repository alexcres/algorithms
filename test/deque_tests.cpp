#include "gtest/gtest.h"
#include "../src/deque/array_deque.h"

using namespace std;

TEST(deque_test, array_deque) {
	array_deque deque;
	for (int i = 0; i < 4; ++i) {
		// test resize
		deque.push_head(i+1);
		deque.push_tail(i+1);
	}
	// 1234 4321
	//test tail before head
	for (int j = 0; j < 4; ++j) {
		deque.pop_tail();
	}
	// 1234xxxx
	EXPECT_EQ(deque.pop_tail(), 1);
	deque.push_tail(5);
	deque.push_tail(6);
	EXPECT_EQ(deque.pop_tail(), 6);

	// 5 234xxxx
	// test head go over the right end
	deque.pop_tail(); // tail == 1
	for (int k = 0; k < 5; ++k) {
		deque.push_head(k + 5);
	}
	// 9 2345678
	EXPECT_EQ(deque.pop_head(), 9);
	EXPECT_EQ(deque.pop_tail(), 2);
}