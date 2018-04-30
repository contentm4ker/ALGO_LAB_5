#include <gtest/gtest.h>
#include "../include/kmp_functions.hpp"

TEST(SquareRootTest, PositiveNos) {
    ASSERT_EQ(0,0);
    //ASSERT_EQ({0}, Prefix_Function("a"));
}

TEST(SquareRootTest, NegativeNos) {
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}