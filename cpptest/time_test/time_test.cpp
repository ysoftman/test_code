////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// time 관련 함수 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	time_t llCurtime = time(NULL);
	printf("llCurtime = %ld\n\n", llCurtime);

	struct tm *tmCurtime = localtime(&llCurtime);
	printf("yday=%d\nwday=%d\nyear=%d\nmon=%d\nmday=%d\nhour=%d\nmin=%d\nsec=%d\nisdst=%d\n\n",
		tmCurtime->tm_yday, // days since January 1 - [0,365]
		tmCurtime->tm_wday, // days since Sunday - [0,6]
		tmCurtime->tm_year+1900, // years since 1900
		tmCurtime->tm_mon+1, // months since January - [0,11]
		tmCurtime->tm_mday, // day of the month - [1,31]
		tmCurtime->tm_hour, // hours since midnight - [0,23]
		tmCurtime->tm_min, // minutes after the hour - [0,59]
		tmCurtime->tm_sec, // seconds after the minute - [0,59]
		tmCurtime->tm_isdst // daylight savings time flag
		);

	time_t llCurtime2 = mktime(tmCurtime);
	printf("llCurtime2 = %ld\n\n", llCurtime2);

	// 윈도우에서는
	// mktime 의 경우 내부적으로 _mktime64 를 사용한다.
	// 만약 _USE_32BIT_TIME_T 를 전처리기로 미리 정의 하였다면 _mktime32 를 사용한다.
	// _mktime32 는 2038년 1월 19일 03:14:07 까지 계산가능한다.
	// _mktime64 는 3000년 12월 31일 23:59:59 까지 계산가능한다.
	// 참고로 리눅스 64비트에서는 3000년 이상 계산 가능하다.
	// 7000년은 3000 년이 지났기 때문에 mktime 이 실패(-1) 한다.
	memset(tmCurtime, 0, sizeof(tm));
	tmCurtime->tm_year = 7000 - 1900;
	llCurtime2 = mktime(tmCurtime);
	printf("llCurtime2 = %ld\n\n", llCurtime2);


	// 문자열 시간 을 time 값으로 
	tm tmResult;
	memset(&tmResult, 0, sizeof(tm));
	std::string timestr;
	timestr = "201705311624";
	cout << timestr << endl;
	if (strptime(timestr.c_str(), "%Y%m%d%H%M", &tmResult) != NULL)
	{
		// cout << tmResult.tm_yday << endl;
		// cout << tmResult.tm_wday << endl;
		cout << "year:" << tmResult.tm_year+1900 << endl;
		cout << "month:" << tmResult.tm_mon+1 << endl;
		cout << "day:" << tmResult.tm_mday << endl;
		cout << "hour:" << tmResult.tm_hour << endl;
		cout << "min:" << tmResult.tm_min << endl;
		cout << "sec:" << tmResult.tm_sec << endl;
		// cout << tmResult.tm_isdst << endl;
		time_t epoch = mktime(&tmResult);
		cout << "epoch:" << epoch << endl;
	}

	return 0;
}

