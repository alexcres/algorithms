#include <gtest/gtest.h>
#include "math/Math.hpp"

TEST(MathTest, Math){
	EXPECT_EQ(Math::gcd(36, 120), 12);
	EXPECT_EQ(Math::lcd(36, 120), 360);
}