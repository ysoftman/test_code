////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ������ ��� �����÷ο�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{
	// warning C4307: '*' : integral constant overflow
	// �Ʒ��� ���� ū ���� ����ϸ� ��꿡 �Ҵ�� ����(4byte)�� �Ѿ �����÷ο� �߻�
	// ���� http://msdn.microsoft.com/ko-kr/library/4kze989h(v=vs.90).aspx
	unsigned long long size1 = 1024 * 1024 * 1024 * 10;
	printf("size1 : %lld\n", size1);
	
	unsigned long long size2 = 1024;
	size2 *= 1024 * 1024 * 10;
	printf("size2 : %lld\n", size2);
}

