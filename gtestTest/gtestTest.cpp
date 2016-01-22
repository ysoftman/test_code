#include <stdio.h>

// gtest-1.7.0 기준 msvc10(vc2010) 까지만 빌드되기 때문에 vc2010 컴파일러 사용해야 함
// 다운로드 https://code.google.com/p/googletest/ 
#ifdef _DEBUG
#pragma comment(lib, "gtest/lib/gtest-vc100-mtd.lib")
#else
#pragma comment(lib, "gtest/lib/gtest-vc100-mt.lib")
#endif

#include "gtest/gtest.h"

TEST(testcase1, testname1)
{
	int a = 10;
	EXPECT_EQ(true, a == 10);
}
TEST(testcase2, testname2)
{
	int a = 10;
	EXPECT_EQ(true, a == 11);
}
TEST(testcase3, testname3)
{
	int a = 11;
	EXPECT_EQ(true, a == 11);
}

int main(int argc, char **argv)
{
	// gtest 초기화
	testing::InitGoogleTest(&argc, argv);
	
	// TEST 함수들에 대한 테스트
	RUN_ALL_TESTS();

	return 0;
}

