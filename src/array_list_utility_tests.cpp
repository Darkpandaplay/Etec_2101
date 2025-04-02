#include <gtest/gtest.h>
#include <array_list_utility.h>

TEST(ALUTest, sorto_bubble)
{
	ssuds::ArrayList<float> flist = { 7.5f,7.1f,2.5f,3.2f,1.0f };
	ssuds::sorto_bubble(flist, ssuds::sort_order::ASCENDING);
	EXPECT_EQ(flist[0], 1.0f);
	EXPECT_EQ(flist[1], 2.5f);
	EXPECT_EQ(flist[2], 3.2f);
	EXPECT_EQ(flist[3], 7.1f);
	EXPECT_EQ(flist[4], 7.5f);
}

TEST(ALUTest, shuffle)
{
	ssuds::ArrayList<float>flist = { 1.1f,2.2f,3.3f,4.4f,5.5f };
	ssuds::shuffle(flist, true);
	EXPECT_NE(flist[0], 1.1f);
	EXPECT_NE(flist[1], 2.2f);
	EXPECT_NE(flist[2], 3.3f);
	EXPECT_NE(flist[3], 4.4f);
	EXPECT_NE(flist[4], 5.5f);
}

TEST(ALUTest, binary_search)
{
	ssuds::ArrayList<float> flist = { 1.1f,2.1f,2.8f,3.8f,4.0f };
	int index = ssuds::binary_search(flist, 3.8f, ssuds::sort_order::ASCENDING);
	EXPECT_EQ(index, 3);
	index = ssuds::binary_search(flist, 0.0f, ssuds::sort_order::ASCENDING);
	EXPECT_EQ(index, -1);
	flist = { 4.0f,3.8f,2.8f,2.1f,1.1f };
	index = ssuds::binary_search(flist, 1.1f, ssuds::sort_order::DESCENDING);
	EXPECT_EQ(index, 4);
}