#include <gtest/gtest.h>
#include "../src/memory/SingleMemory.hpp"
#include "../src/memory/MultiMemory.hpp"
#include "../src/memory/StackMemory.hpp"

TEST(MemoryTest, single_memory) {
	SingleMemory memory;
	for (int i = 0; i < 4; ++i) {
		memory.allocate();
	}
	EXPECT_EQ(memory.allocate(), 0);
	memory.free(1);
	EXPECT_EQ(memory.allocate(), 1);
	memory.free(4);
	memory.free(2);
	EXPECT_EQ(memory.allocate(), 2);
	EXPECT_EQ(memory.allocate(), 4);
	memory.free(3);
	EXPECT_EQ(memory.allocate(), 3);
}

TEST(MemoryTest, multi_memory) {
	MultiMemory memory;
	for (int i = 0; i < 4; ++i) {
		memory.allocate();
	}
	EXPECT_EQ(memory.allocate(), 0);
	memory.free(1);
	EXPECT_EQ(memory.allocate(), 1);
	memory.free(4);
	memory.free(2);
	EXPECT_EQ(memory.allocate(), 2);
	EXPECT_EQ(memory.allocate(), 4);
	memory.free(3);
	EXPECT_EQ(memory.allocate(), 3);
}

TEST(MemoryTest, stack_memory) {
	StackMemory memory{128};
//	EXPECT_EQ(memory.allocate(), 128);

	for (int i = 0; i < 128; ++i) {
		memory.allocate();
	}
	EXPECT_EQ(memory.allocate(), 0);
	memory.free(1);
	EXPECT_EQ(memory.allocate(), 1);
	memory.free(4);
	memory.free(2);
	EXPECT_EQ(memory.allocate(), 2);
	EXPECT_EQ(memory.allocate(), 4);
	memory.free(3);
	EXPECT_EQ(memory.allocate(), 3);

}