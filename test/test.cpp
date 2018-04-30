#include <gtest/gtest.h>
#include "kmp_functions.cpp"

void Vectors_Comparison(vector<int> v1, vector<int> v2) {
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST(KmpTest, Positions) {
    vector<int> arrange_positions;
    vector<int> positions;

    KMP("xyz", "a", positions);
    ASSERT_EQ(1, positions.size())
    << "Vector size returning in Prefix Function must be eq 1";
    Vectors_Comparison({-1}, positions);

    KMP("aabaabaaaabaabaaab", "aabaa", positions);
    ASSERT_EQ(4, positions.size())
    << "Vector size returning in Prefix Function must be eq 1";
    Vectors_Comparison({0, 3, 8, 11}, positions);

    string p(15000, 'a');
    string t1(5000000, 'b');
    arrange_positions.resize(0);
    arrange_positions.push_back(-1);
    KMP(t1, p, positions);
    Vectors_Comparison(arrange_positions, positions);

    string t2(5000000, 'a');
    arrange_positions.resize(4985001);
    int c = -1;
    for(auto& item : arrange_positions) {
        item = ++c;
    }
    KMP(t2, p, positions);
    Vectors_Comparison(arrange_positions, positions);
}

TEST(KmpTest, PrefixFunction) {
    ASSERT_EQ(1, Prefix_Function("a").size())
    << "Vector size returning in Prefix Function must be eq 1";
    Vectors_Comparison({0}, Prefix_Function("a"));

    ASSERT_EQ(5, Prefix_Function("aabaa").size())
    << "Vector size returning in Prefix Function must be eq 5";
    Vectors_Comparison({0, 1, 0, 1, 2}, Prefix_Function("aabaa"));

    ASSERT_EQ(7, Prefix_Function("aabaaab").size())
    << "Vector size returning in Prefix Function must be eq 7";
    Vectors_Comparison({0, 1, 0, 1, 2, 2, 3}, Prefix_Function("aabaaab"));

    string p(15000, 'a');
    vector<int> arrange_pf(15000);
    int c = -1;
    for(auto& item : arrange_pf) {
        item = ++c;
    }
    Vectors_Comparison(arrange_pf, Prefix_Function(p));
}

TEST(ShiftTest, Shifts) {
    string A = "defabc";
    string B = "abcdef";
    ASSERT_EQ(3, KMP_Returning_First_Pos(A + A, B));

    A = "abcdefghijklmn";
    B = "fghijklmnabcde";
    ASSERT_EQ(5, KMP_Returning_First_Pos(A + A, B));

    A = "abababab";
    B = "babababa";
    ASSERT_EQ(1, KMP_Returning_First_Pos(A + A, B));

    A = "aa";
    B = "a";
    ASSERT_EQ(-1, KMP_Returning_First_Pos(A + A, B));

    A = "a";
    B = "aa";
    ASSERT_EQ(-1, KMP_Returning_First_Pos(A + A, B));

    string A1(5000000, 'a');
    string B1(5000000, 'a');
    ASSERT_NO_THROW(KMP_Returning_First_Pos(A1 + A1, B1));
    ASSERT_EQ(0, KMP_Returning_First_Pos(A1 + A1, B1));

    string B2(5000000, 'b');
    ASSERT_NO_THROW(KMP_Returning_First_Pos(A1 + A1, B2));
    ASSERT_EQ(-1, KMP_Returning_First_Pos(A1 + A1, B2));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}