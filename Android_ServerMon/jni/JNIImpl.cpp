////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// JNI(Java Native Interface) java 에서 사용할 C 코드
// visual c++ 에서 메뉴에서 jdk include 경로 추가하기
// 도구 -> 옵션 -> 프로젝트 및 솔루션 -> VC++ 디렉터리 -> 포함파일 -> 다음의 JDK include 경로 추가
// C:\Program Files (x86)\Java\jdk1.7.0_15\include
// C:\Program Files (x86)\Java\jdk1.7.0_15\include\win32
// 이 코드는 dll 로 구성(출력)하도록 설정한다.
// 구성속성->일반->구성형식->동적 라이브러리 (.dll) 선택
// 구성속성->링커->일반->출력파일명에.dll
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "com_Android_ServerMon_JNIManager.h"

JNIEXPORT void JNICALL Java_com_Android_1ServerMon_JNIManager_Print(JNIEnv *env, jobject obj)
{
	printf("This C Java_JNIManager_Print()\n");
	return;
}
JNIEXPORT jint JNICALL Java_com_Android_1ServerMon_JNIManager_Add(JNIEnv *env, jobject obj, jint a, jint b)
{
	printf("This C Java_JNIManager_Add()\n");
	// java 타입으로 결과값 저장하여 리턴
	jint sum;
	sum = a+b;
	return sum;
}
JNIEXPORT jstring JNICALL Java_com_Android_1ServerMon_JNIManager_PrintString(JNIEnv *env, jobject obj, jstring msg)
{
	printf("This C Java_JNIManager_PrintString()\n");
	// java 의 2바이트(16비트) 문자열을 C 의 1바이트(8비트) 문자열로 변환
	const char *szStr = env->GetStringUTFChars(msg, 0);

	printf("string from java : %s", szStr);
	char szBuffer[1024];
	memset(szBuffer, 0, sizeof(szBuffer));
	strcat(szBuffer, "Name: ");
	strcat(szBuffer, szStr);

	// JVM 에게 문자열 사용이 끝났다고 알려주고 메모리 해지
	env->ReleaseStringUTFChars(msg, szStr);

	// C 의 멀티바이트 문자열을 java 의 유니코드로 변환하여 리턴
	return env->NewStringUTF(szBuffer);
}
