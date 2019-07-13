#include <gtest/gtest.h>
#include <mpp/algorithm.hpp>

const int float1 = 0x3F800000;

TEST(algorithm, bit_cast)
{
    const int res = mpp::by_bit_cast<float, int>(1.0f);
    ASSERT_EQ(float1, res);
}

TEST(algorithm, split)
{
    std::vector<int> check = {1,2,3,0,4,5,6,0,7,8,9};
    auto res = mpp::split(check.begin(), check.end(), 0);
    ASSERT_EQ(res.size(), 3);

    ASSERT_EQ(res[0].size(), 3);
    ASSERT_EQ(res[0][0], 1);
    ASSERT_EQ(res[0][1], 2);
    ASSERT_EQ(res[0][2], 3);

    ASSERT_EQ(res[1].size(), 3);
    ASSERT_EQ(res[1][0], 4);
    ASSERT_EQ(res[1][1], 5);
    ASSERT_EQ(res[1][2], 6);

    ASSERT_EQ(res[2].size(), 3);
    ASSERT_EQ(res[2][0], 7);
    ASSERT_EQ(res[2][1], 8);
    ASSERT_EQ(res[2][2], 9);

    std::vector<int> check2 = {0,0, 1,2,3,0,0, 3, 0};
    res = mpp::split(check2.begin(), check2.end(), 0);
    ASSERT_EQ(res.size(), 2);
    ASSERT_EQ(res[0].size(), 3);
    ASSERT_EQ(res[0][0], 1);
    ASSERT_EQ(res[0][1], 2);
    ASSERT_EQ(res[0][2], 3);
    ASSERT_EQ(res[1].size(), 1);
    ASSERT_EQ(res[1][0], 3);
}

TEST(algorithm, split_string)
{
    std::string check = "Hello, world, you, suck";
    auto res = mpp::split(check.begin(), check.end(), ',');
    ASSERT_EQ(res.size(), 4);
    ASSERT_STREQ(res[0].c_str(), "Hello");
    ASSERT_STREQ(res[1].c_str(), " world");
    ASSERT_STREQ(res[2].c_str(), " you");
    ASSERT_STREQ(res[3].c_str(), " suck");
}

TEST(algorithm, starts_with)
{
    std::string check = "Kokoro";
    ASSERT_EQ(true, mpp::starts_with(check, "Ko"));
    ASSERT_EQ(false, mpp::starts_with(check, "ko"));
    ASSERT_EQ(false, mpp::starts_with(check, "Kokoro4o"));
}

TEST(algorithm, ends_with)
{
    std::string check = "Kokoro";
    ASSERT_EQ(true, mpp::ends_with(check, "ro"));
    ASSERT_EQ(false, mpp::ends_with(check, "rro"));
    ASSERT_EQ(false, mpp::ends_with(check, "Okokoro"));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}