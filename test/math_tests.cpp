#include <gtest/gtest.h>
#include "../src/math/math.h"

TEST(MathTest, Math){
	EXPECT_EQ(math::gcd(36, 120), 12);
	EXPECT_EQ(math::lcd(36, 120), 360);
}