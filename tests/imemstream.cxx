#include <gtest/gtest.h>
#include <mpp/memory/imemstream.hpp>

TEST (imemstream, concurency) 
{
    mpp::imemstream stream;
    stream  << (char) 10
            << (short) 11
            << (int) 14;

    auto get = stream.get();
    ASSERT_EQ((int)get[0], 10);
    ASSERT_EQ((int)get[1], 11);
    ASSERT_EQ((int)get[2], 0);
    ASSERT_EQ((int)get[3], 14);
    ASSERT_EQ((int)get[4], 0);
    ASSERT_EQ((int)get[5], 0);
    ASSERT_EQ((int)get[6], 0);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}