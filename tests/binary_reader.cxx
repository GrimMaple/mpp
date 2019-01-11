#include <gtest/gtest.h>
#include <mpp/io/binary_reader.hpp>

TEST (binary_reader, concurency)
{
	char arr[] = {0, 1, 2, 3, 4};
	char test[] = {-1, 0, 0, 0, 0};

	FILE *f = fopen("test.reader", "wb");
	fwrite(arr, 1, 5, f);
	fclose(f);

	mpp::binary_reader stream("test.reader");
    	stream  >> test[0]
		>> test[1]
		>> test[2]
		>> test[3]
          	>> test[4];  

	ASSERT_EQ(test[0], 0);
	ASSERT_EQ(test[1], 1);
	ASSERT_EQ(test[2], 2);
	ASSERT_EQ(test[3], 3);
	ASSERT_EQ(test[4], 4);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

