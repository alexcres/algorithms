#include "gtest/gtest.h"
#include "../src/queue/ListQueue.hpp"
#include "../src/queue/ArrayQueue.hpp"
#include "../src/queue/TwoStackQueue.hpp"

TEST(QueueTest, list_queue) {
	ListQueue queue;
	for (int i = 0; i < 4; ++i) {
		queue.enqueue(i);
	}
	EXPECT_EQ(queue.dequeue(), 0);
	EXPECT_EQ(queue.dequeue(), 1);
	EXPECT_EQ(queue.dequeue(), 2);
	EXPECT_EQ(queue.dequeue(), 3);
	try {
		queue.dequeue();
	}
	catch (std::out_of_range const &err) {
		EXPECT_EQ(err.what(), std::string("list_queue Underflow"));
	}
}

TEST(QueueTest, array_queue) {
	ArrayQueue queue;
	for (int i = 0; i < 4; ++i) {
		queue.enqueue(i);
	}
	EXPECT_EQ(queue.dequeue(), 0);
	EXPECT_EQ(queue.dequeue(), 1);
	queue.enqueue(4);
	queue.enqueue(5);
	queue.enqueue(6);
	EXPECT_EQ(queue.dequeue(), 2);
	EXPECT_EQ(queue.dequeue(), 3);
	EXPECT_EQ(queue.dequeue(), 4);
	EXPECT_EQ(queue.dequeue(), 5);
	EXPECT_EQ(queue.dequeue(), 6);
	try {
		queue.dequeue();
	}
	catch (std::out_of_range const &err) {
		EXPECT_EQ(err.what(), std::string("array_queue Underflow"));
	}
}

TEST(QueueTest, two_stack_queue) {
	TwoStackQueue queue;
	for (int i = 0; i < 4; ++i) {
		queue.enqueue(i);
	}
	EXPECT_EQ(queue.dequeue(), 0);
	EXPECT_EQ(queue.dequeue(), 1);
	queue.enqueue(4);
	queue.enqueue(5);
	queue.enqueue(6);
	EXPECT_EQ(queue.dequeue(), 2);
	EXPECT_EQ(queue.dequeue(), 3);
	EXPECT_EQ(queue.dequeue(), 4);
	EXPECT_EQ(queue.dequeue(), 5);
	EXPECT_EQ(queue.dequeue(), 6);
}