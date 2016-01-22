////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// time ���� �Լ� �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <time.h>
#include <string.h>

int main()
{
	time_t llCurtime = time(NULL);
	printf("llCurtime = %lld\n\n", llCurtime);

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
	printf("llCurtime2 = %lld\n\n", llCurtime2);

	// �����쿡����
	// mktime �� ��� ���������� _mktime64 �� ����Ѵ�.
	// ���� _USE_32BIT_TIME_T �� ��ó����� �̸� ���� �Ͽ��ٸ� _mktime32 �� ����Ѵ�.
	// _mktime32 �� 2038�� 1�� 19�� 03:14:07 ���� ��갡���Ѵ�.
	// _mktime64 �� 3000�� 12�� 31�� 23:59:59 ���� ��갡���Ѵ�.
	// ����� ������ 64��Ʈ������ 3000�� �̻� ��� �����ϴ�.
	// 7000���� 3000 ���� ������ ������ mktime �� ����(-1) �Ѵ�.
	memset(tmCurtime, 0, sizeof(tm));
	tmCurtime->tm_year = 7000 - 1900;
	llCurtime2 = mktime(tmCurtime);
	printf("llCurtime2 = %lld\n\n", llCurtime2);

	return 0;
}

