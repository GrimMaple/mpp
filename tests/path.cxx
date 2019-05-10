#include <gtest/gtest.h>
#include <mpp/io/path.hpp>

#include <iostream>

TEST(path, create)
{
    mpp::path a("C:\\123/");
    ASSERT_STREQ(a.get().c_str(), "C:/123/");

    mpp::path b("C:\\\\Windows\\System32////123");
    ASSERT_STREQ(b.get().c_str(), "C:/Windows/System32/123");
}

TEST(path, concat)
{
    mpp::path a("C:\\");
    auto res = a + "Windows";

    ASSERT_STREQ(res.get().c_str(), "C:/Windows");

    res = res + "System32";
    ASSERT_STREQ(res.get().c_str(), "C:/Windows/System32");

    res += "drivers";
    ASSERT_STREQ(res.get().c_str(), "C:/Windows/System32/drivers");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
