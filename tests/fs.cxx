#include <gtest/gtest.h>
#include <mpp/io/directory_info.hpp>

#include <iostream>

#ifdef WIN32
TEST(fs, create)
{
    mpp::directory_info di(std::string("C:\\Windows"));
    bool has_self = false;

    ASSERT_STREQ(di.get_path().get().c_str(), "C:/Windows");
    ASSERT_STREQ(di.get_name().c_str(), "Windows");

    auto dirs = di.get_directories();
    bool found = false;
    mpp::directory_info inf(std::string("."));
    for(const auto& i : dirs)
    {
        if(i.get_name() == "System32")
        {
            inf = i;
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);
    ASSERT_STREQ(inf.get_name().c_str(), "System32");
    ASSERT_STREQ(inf.get_path().get().c_str(), "C:/Windows/System32");
}
#else
TEST(fs, create)
{
    mpp::directory_info di(std::string("/usr"));

    ASSERT_STREQ(di.get_path().get().c_str(), "/usr");
    ASSERT_STREQ(di.get_name().c_str(), "usr");

    auto dirs = di.get_directories();
    bool found = false;
    mpp::directory_info inf(std::string("."));
    for(const auto& i : dirs)
    {
        if(i.get_name() == "local")
        {
            inf = i;
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);
    ASSERT_STREQ(inf.get_name().c_str(), "local");
    ASSERT_STREQ(inf.get_path().get().c_str(), "/usr/local");
}
#endif

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
