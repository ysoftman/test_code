#include <stdio.h>

// gtest-1.7.0 ���� msvc10(vc2010) ������ ����Ǳ� ������ vc2010 �����Ϸ� ����ؾ� ��
// �ٿ�ε� https://code.google.com/p/googletest/ 
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
	// gtest �ʱ�ȭ
	testing::InitGoogleTest(&argc, argv);
	
	// TEST �Լ��鿡 ���� �׽�Ʈ
	RUN_ALL_TESTS();

	return 0;
}

