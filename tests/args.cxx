#include <gtest/gtest.h>
#include <mpp/args.hpp>

TEST (args, parse)
{
    int argc = 11;
#ifdef WIN32
    const char * const  argv[]  = 
    {
        "someexe",
        "r",
        "t",
        "y",
        "/t",
        "a",
        "b",
        "c",
        "/d",
        "/help",
        "/h"
    };
#else
    const char * const  argv[]  = 
    {
        "someexe",
        "r",
        "t",
        "y",
        "-t",
        "a",
        "b",
        "c",
        "-d",
        "--help",
        "-h"
    };
#endif
    mpp::args args = mpp::args::parse(argc, argv);
    ASSERT_TRUE(args.has("t"));
    ASSERT_TRUE(args.has("d"));
    ASSERT_TRUE(args.has("help"));
    ASSERT_TRUE(args.has("h"));
    ASSERT_EQ(args.get_values("t").size(), 3);
    ASSERT_EQ(args.get_unnamed_values().size(), 4);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

