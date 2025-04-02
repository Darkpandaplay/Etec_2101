#include <gtest/gtest.h>

#define EXECUTE_ARRAY_LIST_TESTS 1
//#if EXECUTE_ARRAY_LIST_TESTS

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}