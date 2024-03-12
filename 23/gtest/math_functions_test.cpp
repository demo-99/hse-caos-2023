#include "math_functions.h"
#include <gtest/gtest.h>

TEST(MathFunctionsTest, PositiveNumbers) {
    EXPECT_EQ(5, add(2, 3));
}

TEST(MathFunctionsTest, NegativeNumbers) {
    EXPECT_EQ(-5, add(-2, -3));
}

TEST(MathFunctionsTest, PositiveAndNegativeNumbers) {
    EXPECT_EQ(1, add(-2, 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
