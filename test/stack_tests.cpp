#include "gtest/gtest.h"
#include "../src/stack/array_stack.h"
#include "../src/stack/list_stack.h"
#include "../src/stack/smart_list_stack.h"
#include "../src/stack/two_stack_array.h"
#include "../src/stack/two_queue_stack.h"


//class StackTest : public ::testing::Test {
//protected:
//	void SetUp() override {
//		for (int i = 0; i != 8; ++i) {
//			a_stack.push(i);
//		}
//	};
//
//	void TearDown() override {
//	};
//
//	array_stack<int> a_stack;
//};

TEST(StackTest, array_stack) {
	array_stack<int> a_stack;
	for (int i=0; i != 8; ++i) {
		a_stack.push(i);
	}
	EXPECT_EQ(a_stack.get_capacity(), 8);
	for (int i = 0; i != 6; ++i) {
		a_stack.pop();
	}
	EXPECT_EQ(a_stack.get_capacity(), 4);
	try {
		for (int i = 0; i != 3; ++i) {
			a_stack.pop();
		}
	}
	catch (std::out_of_range const &err) {
		EXPECT_EQ(err.what(), std::string("array_stack Underflow"));
	}
	EXPECT_EQ(a_stack.get_capacity(), 2);
}

TEST(StackTest, list_stack) {
	list_stack<int> l_stack;
	for (int i = 0; i != 8; ++i) {
		l_stack.push(i);
	}
	EXPECT_EQ(l_stack.pop(), 8);
}

TEST(StackTest, smart_list_stack) {
	smart_list_stack<int> s_stack;
	for (int i = 0; i < 8; ++i) {
		s_stack.push(i);
	}
	EXPECT_EQ(s_stack.pop(), 7);
}

TEST(StackTest, two_stack_array) {
	two_stack_array stack{8};
	// fill stack
	for (int i = 0; i < 4; ++i) {
		stack.push(i+1);
		stack.push(i+1, false);
	}
	EXPECT_EQ(stack.pop(), 4);
	EXPECT_EQ(stack.pop(false), 4);
	stack.push(4);
	stack.push(5);
	EXPECT_EQ(stack.pop(false), 3);
	stack.push(6);
}

TEST(StackTest, two_queue_stack) {
	two_queue_stack s_stack;
	for (int i = 0; i < 8; ++i) {
		s_stack.push(i);
	}
	EXPECT_EQ(s_stack.pop(), 7);
}