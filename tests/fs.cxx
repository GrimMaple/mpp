#include <gtest/gtest.h>
#include <mpp/io/directory_info.hpp>

#include <iostream>

TEST(fs, read_directory)
{
    mpp::directory_info di("c:\\");
    bool has_self = false;
    for(auto& i : di.get_files())
        std::cout << i.get_path() << " -- " << i.get_size() << " bytes" << std::endl;

    for(auto& i : di.get_directories())
        std::cout<<i.get_path() << std::endl;
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
