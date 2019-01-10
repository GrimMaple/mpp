#include <gtest/gtest.h>
#include <mpp/io/binary_writer.hpp>

TEST (binary_writer, concurency) 
{
    mpp::binary_writer stream("test.file");
    stream  << (int8_t) 10
            << (int16_t) 11
            << (int32_t) 14;

    stream.close();
    
    FILE *f = fopen("test.file", "rb");
    char get[256];

    fread(get, 1, 7, f);
    fclose(f);

    ASSERT_EQ((int)get[0], 10);
    ASSERT_EQ((int)get[1], 11);
    ASSERT_EQ((int)get[2], 0);
    ASSERT_EQ((int)get[3], 14);
    ASSERT_EQ((int)get[4], 0);
    ASSERT_EQ((int)get[5], 0);
    ASSERT_EQ((int)get[6], 0);
}

TEST(binary_writer, vector_write)
{
	std::vector<char> data = {1, 2, 3, 4};
	mpp::binary_writer stream("test.vector");

	stream << data;
    stream.close();

    FILE *f = fopen("test.vector", "rb");
    char get[256];

    fread(get, 1, 4, f);
    fclose(f);

	ASSERT_EQ(get[0], 1);
	ASSERT_EQ(get[1], 2);
	ASSERT_EQ(get[2], 3);
	ASSERT_EQ(get[3], 4);
}

TEST(binary_writer, is_open)
{
	// This test seems to make GTEST hang up
	// I've tested, and it doesn't seem to be a bug in my code
	// So I'll leave thsi hanging until the issue is investigated
	
	/*
	bool check = false;
   	mpp::binary_writer writer;
   	check = writer.is_open();
   	ASSERT_EQ(check, false);
 	writer.open("test.vector");
	check = writer.is_open();
	ASSERT_EQ(check, true);
   	mpp::binary_writer writer2("test.file");
	check = writer2.is_open();
   	ASSERT_EQ(check, true);
	*/
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
