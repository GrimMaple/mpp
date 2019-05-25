#include <gtest/gtest.h>
#include <mpp/io/path.hpp>

#include <iostream>

TEST(path, create)
{
    #ifdef WIN32
    mpp::path a("C:\\123/");
    ASSERT_STREQ(a.get().c_str(), "C:/123/");

    mpp::path b("C:\\\\Windows\\System32////123");
    ASSERT_STREQ(b.get().c_str(), "C:/Windows/System32/123");
    #endif

    mpp::path c("/some///re////ally/////test//stuff");
    ASSERT_STREQ(c.get().c_str(), "/some/re/ally/test/stuff");
}

TEST(path, ctors)
{
    mpp::path a;
    #ifdef WIN32
    ASSERT_STREQ(a.get().c_str(), "C:/");
    #else
    ASSERT_STREQ(a.get().c_str(), "/");
    #endif
}

TEST(path, conv)
{
    mpp::path a("/sample/path");
    std::string test = a;
    ASSERT_STREQ(test.c_str(), "/sample/path");
}

TEST(path, concat)
{
    mpp::path a("C:/");
    auto res = a + "Windows";

    ASSERT_STREQ(res.get().c_str(), "C:/Windows");

    res = res + "System32";
    ASSERT_STREQ(res.get().c_str(), "C:/Windows/System32");

    res += "drivers";
    ASSERT_STREQ(res.get().c_str(), "C:/Windows/System32/drivers");
}

TEST(path, last_item)
{
    mpp::path a("C:/Windows");
    ASSERT_STREQ(a.last_entry().c_str(), "Windows");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
