#include <gtest/gtest.h>
#include <mpp/io/file.hpp>

#include <mpp/io/binary_writer.hpp>
#include <fstream>

using namespace mpp;

void create_test_file()
{
    binary_writer bw("test-file");
    bw << (int8_t) 100 
        << (int8_t) 125
        << (int16_t) 1000
        << (int32_t) 0;
}

void delete_test_file()
{
    remove("test-file");
}

void create_test_text_file()
{
    std::ofstream s;
    s.open("test-file");
    s   << "Hello, world!"
        << std::endl
        << "How are you?"
        << std::endl
        << std::endl
        << "\t"
        << std::endl
        << "\r\t\0\r\n";
}

TEST(file, read_fully)
{
    create_test_file();

    auto res = file::read_fully("test-file");
    ASSERT_EQ(res.size(), 8);
    ASSERT_EQ(res[0], 100);
    ASSERT_EQ(res[1], 125);
    ASSERT_EQ(res[6], 0);

    res = file::read_fully(std::string("test-file"));
    ASSERT_EQ(res.size(), 8);
    ASSERT_EQ(res[0], 100);
    ASSERT_EQ(res[1], 125);
    ASSERT_EQ(res[6], 0);

    delete_test_file();
}

TEST(file, read_all_lines)
{
    create_test_text_file();

    auto res = file::read_all_lines("test-file");
    ASSERT_EQ(res.size(), 5);

    res = file::read_all_lines(std::string("test-file"));

    delete_test_file();
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
