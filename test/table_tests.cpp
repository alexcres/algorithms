#include <gtest/gtest.h>
#include "../src/table/HashTable.hpp"

TEST(TableTest, hash_table) {
	HashTable table;
	for (int i = 1; i < 11; ++i) {
		table.insert(i);
		EXPECT_EQ(table.search(i), true);
	}
	for (int i = 11; i < 27; ++i) {
		EXPECT_EQ(table.search(i), false);
	}
	for (int i = 1; i < 11; ++i) {
		if (i%2 == 0) {
			table.remove(i);
			EXPECT_EQ(table.search(i), false);
		} else {
			EXPECT_EQ(table.search(i), true);
		}
	}
}