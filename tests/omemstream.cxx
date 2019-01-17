#include <gtest/gtest.h>
#include <mpp/memory/omemstream.hpp>

TEST(omemstream, concurency)
{
	std::vector<uint8_t> bytes{ 10, 11, 0, 14, 0, 0, 0 };
	mpp::omemstream stream(bytes.data(), 7);
	char a;
	short b;
	int c;
	stream >> a >> b >> c;

	ASSERT_EQ(a, 10);
	ASSERT_EQ(b, 11);
	ASSERT_EQ(c, 14);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
