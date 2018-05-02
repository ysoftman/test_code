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

void printTM(struct tm *t)
{
	printf("yday=%d\nwday=%d\nyear=%d\nmon=%d\nmday=%d\nhour=%d\nmin=%d\nsec=%d\nisdst=%d\n",
		   t->tm_yday,		  // days since January 1 - [0,365]
		   t->tm_wday,		  // days since Sunday - [0,6]
		   t->tm_year + 1900, // years since 1900
		   t->tm_mon + 1,	 // months since January - [0,11]
		   t->tm_mday,		  // day of the month - [1,31]
		   t->tm_hour,		  // hours since midnight - [0,23]
		   t->tm_min,		  // minutes after the hour - [0,59]
		   t->tm_sec,		  // seconds after the minute - [0,59]
		   t->tm_isdst		  // daylight savings time flag
	);
}
// 문자열 시간 을 time 값으로
void string2time(string timestr)
{
	cout << "[string2time] " << timestr << endl;

	tm tmResult;
	memset(&tmResult, 0, sizeof(tm));
	if (strptime(timestr.c_str(), "%Y%m%d%H%M", &tmResult) != NULL)
	{
		cout << "year:" << tmResult.tm_year + 1900 << endl;
		cout << "month:" << tmResult.tm_mon + 1 << endl;
		cout << "day:" << tmResult.tm_mday << endl;
		cout << "wday:" << tmResult.tm_wday << endl;
		cout << "hour:" << tmResult.tm_hour << endl;
		cout << "min:" << tmResult.tm_min << endl;
		cout << "sec:" << tmResult.tm_sec << endl;
		// cout << tmResult.tm_isdst << endl;
		time_t epoch = mktime(&tmResult);
		cout << "epoch:" << epoch << endl;
	}
	cout << endl;
}

// 현재 unix 시간을 UTC(Universal Time Convention) 스트링으로 출력하기
void unix2utc(time_t now)
{
	cout << "[unix2utc] " << now << endl;

	// UTC(GMT timezone) 시간으로 변경
	tm *tmGnow = gmtime(&now);
	printTM(tmGnow);

	char out[100] = {
		0,
	};

	// %a	Abbreviated weekday name	Sun
	// %A	Full weekday name	Sunday
	// %b	Abbreviated month name	Mar
	// %B	Full month name	March
	// %c	Date and time representation	Sun Aug 19 02:56:02 2012
	// %d	Day of the month (01-31)	19
	// %H	Hour in 24h format (00-23)	14
	// %I	Hour in 12h format (01-12)	05
	// %j	Day of the year (001-366)	231
	// %m	Month as a decimal number (01-12)	08
	// %M	Minute (00-59)	55
	// %p	AM or PM designation	PM
	// %S	Second (00-61)	02
	// %U	Week number with the first Sunday as the first day of week one (00-53)	33
	// %w	Weekday as a decimal number with Sunday as 0 (0-6)	4
	// %W	Week number with the first Monday as the first day of week one (00-53)	34
	// %x	Date representation	08/19/12
	// %X	Time representation	02:50:06
	// %y	Year, last two digits (00-99)	01
	// %Y	Year	2012
	// %Z	Timezone name or abbreviation	CDT
	// %%	A % sign	%

	// 다음과 같은 형식으로 출력
	// Wed, 21 Oct 2015 07:28:00 UTC
	strftime(out, sizeof(out), "%a, %d %b %Y %X %Z", localtime(&now));
	cout << "strtime(local):" << out << endl;
	memset(out, 0, sizeof(out));
	strftime(out, sizeof(out), "%a, %d %b %Y %X %Z", tmGnow);
	cout << "strtime(utc):" << out << endl;

	cout << endl;
}

int main()
{
	time_t llCurtime = time(NULL);
	printf("llCurtime = %ld\n", llCurtime);
	struct tm *tmCurtime = localtime(&llCurtime);
	printTM(tmCurtime);
	cout << endl;

	unix2utc(llCurtime);

	string2time("201705311624");

	// 윈도우에서는
	// mktime 의 경우 내부적으로 _mktime64 를 사용한다.
	// 만약 _USE_32BIT_TIME_T 를 전처리기로 미리 정의 하였다면 _mktime32 를 사용한다.
	// _mktime32 는 2038년 1월 19일 03:14:07 까지 계산가능한다.
	// _mktime64 는 3000년 12월 31일 23:59:59 까지 계산가능한다.
	// 참고로 리눅스 64비트에서는 3000년 이상 계산 가능하다.
	// 7000년은 3000 년이 지났기 때문에 mktime 이 실패(-1) 한다.
	memset(tmCurtime, 0, sizeof(tm));
	tmCurtime->tm_year = 7000 - 1900;
	time_t llCurtime2 = mktime(tmCurtime);
	printf("llCurtime2 = %ld\n\n", llCurtime2);
	llCurtime2 = mktime(tmCurtime);
	printf("llCurtime2 = %ld\n\n", llCurtime2);

	return 0;
}
