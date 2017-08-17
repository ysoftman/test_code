////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// signal 처리 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler_sig_int(int sig)
{
	printf("%s(%d) signal(%d) received.\n", __FUNCTION__, __LINE__, sig);

}

int main()
{
	printf("%s(%d) program start.\n", __FUNCTION__, __LINE__);

	// signal handling, 시그널 핸들러 등록
	signal(SIGINT, handler_sig_int);
		
	unsigned int cnt = 1;
	while (cnt <= 20)
	{
		printf("%d\n", cnt);
		_sleep(1000);

		if (cnt == 10)
		{
			// send a signal to the caller, 시그널 발생
			raise(SIGINT);
		}
		cnt++;
	}
	
	printf("%s(%d) program end.\n", __FUNCTION__, __LINE__);
	return 0;

}


