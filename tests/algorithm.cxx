#include <gtest/gtest.h>
#include <mpp/algorithm.hpp>

const int float1 = 0x3F800000;

TEST(algorithm, bit_cast)
{
    const int res = mpp::by_bit_cast<float, int>(1.0f);
    ASSERT_EQ(float1, res);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}