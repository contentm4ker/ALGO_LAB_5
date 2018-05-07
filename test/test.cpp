#include <gtest/gtest.h>
#include "kmp_functions.cpp"

namespace {

using ::testing::TestWithParam;
using ::testing::Values;

struct StrSearchTest
{
    string text;
	string pattern;
	vector<int> expected_kmp;
	vector<int> expected_prefix;
};

class StrSearchTestFixture : public TestWithParam<StrSearchTest>
{
public:
	virtual void SetUp() {
	    string _text = GetParam().text;
	    string _pattern = GetParam().pattern;
	    KMP(_text, _pattern, kmp_v);
	    prefix = Prefix_Function(_pattern);
	}
    virtual void TearDown() { }

protected:
    vector<int> kmp_v;
	vector<int> prefix;
};

vector<int> getVecWithNumSeq(size_t size) {
    vector<int> vec(size);
    int c = -1;
    for(auto& item : vec) {
        item = ++c;
    }
    return vec;
}

INSTANTIATE_TEST_CASE_P(StrSearchTestInstantiate, StrSearchTestFixture,
Values(
    StrSearchTest{"xyz", "a", {-1}, {0}},
	StrSearchTest{"aaaa", "", {-1}, {}},
	StrSearchTest{"aabaaab", "aabaaab", {0}, {0, 1, 0, 1, 2, 2, 3}},
    StrSearchTest{string (5000000, 'b'), string (15000, 'a'), {-1}, getVecWithNumSeq(15000)},
    StrSearchTest{string (5000000, 'a'), string (15000, 'a'),
    getVecWithNumSeq(4985001), getVecWithNumSeq(15000)}
));


void Vectors_Comparison(vector<int> v1, vector<int> v2) {
    for (size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]) << "Vectors x and y differ at index " << i;
    }
}

TEST_P(StrSearchTestFixture, KmpTest) {
    ASSERT_EQ(GetParam().expected_kmp.size(), kmp_v.size())
    << "Vector size returning in KMP must be eq " << GetParam().expected_kmp.size();
    Vectors_Comparison(GetParam().expected_kmp, kmp_v);

    ASSERT_EQ(GetParam().expected_prefix.size(), prefix.size())
    << "Vector size returning in Prefix Function must be eq " << GetParam().expected_prefix.size();
    Vectors_Comparison(GetParam().expected_prefix, prefix);
}

struct StrShiftTest
{
    string A;
	string B;
	int exp_shift_pos;
};

class StrShiftTestFixture : public TestWithParam<StrShiftTest>
{
public:
	virtual void SetUp() {
	    shift_pos = KMP_Returning_First_Pos
	               (GetParam().A + GetParam().A, GetParam().B);
	}
    virtual void TearDown() { }

protected:
	int shift_pos;
};

INSTANTIATE_TEST_CASE_P(StrShiftInstantiation, StrShiftTestFixture,
Values(
	StrShiftTest{"defabc", "abcdef", 3},
	StrShiftTest{"abcdefghijklmn", "fghijklmnabcde", 5},
	StrShiftTest{"abababab", "babababa", 1},
	StrShiftTest{"aa", "a", -1},
	StrShiftTest{"a", "aa", -1},
	StrShiftTest{string (5000000, 'a'), string (5000000, 'a'), 0},
	StrShiftTest{string (5000000, 'a'), string (5000000, 'b'), -1}
));

TEST_P(StrShiftTestFixture, Shifts) {
    ASSERT_EQ(GetParam().exp_shift_pos, shift_pos);
}

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}