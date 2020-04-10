#include <gtest/gtest.h>
#include "../src/memory/single_memory.h"
#include "../src/memory/multi_memory.h"
#include "../src/memory/stack_memory.h"

TEST(MemoryTest, single_memory) {
	single_memory memory;
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
	multi_memory memory;
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
	stack_memory memory{128};
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