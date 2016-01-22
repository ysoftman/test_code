////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// linux ���� �׽�Ʈ ���α׷�
////////////////////////////////////////////////////////////////////////////////////
#ifdef linux
#include <stdio.h>
#include <unistd.h>

int main()
{
	// fork() �� ���纻(�ڽ�) ���μ����� �����, �ᱹ 2���� ���μ����� ������� �ȴ�.
	// ������ ���� ���,
	// fork() �� ���� ���μ������Դ� ���纻 ���μ����� ID�� �����ϰ�, ���纻 ���μ������Դ� 0�� �����Ѵ�.
	int pid = fork();
	switch (pid)
	{
	case -1:
		fprintf(stderr, "fork filed.\n");
		break;
		// ���纻(�ڽ�) ���μ����� ��� ��� �۾� ����(���� ���μ����� �۵�)
	case 0:
		fprintf(stderr, "fork succeed.\n");
		break;
		// ����(�θ�) ���μ����� ��� ���α׷� ����
	default:
		fprintf(stderr, "child process id : %d\n", pid);
		return 0;
	}

	// ���纻(�ڽ�) ���μ����� �۾��� �����Ѵ�.
	int count = 0;
	while (1)
	{
		fprintf(stderr, "ysoftmand count=%d\n", count++);
		// 2�ʰ��� ������
		sleep(2);
	}
	return 0;
}
#endif


