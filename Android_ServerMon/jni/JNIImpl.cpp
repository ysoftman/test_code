////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// JNI(Java Native Interface) java ���� ����� C �ڵ�
// visual c++ ���� �޴����� jdk include ��� �߰��ϱ�
// ���� -> �ɼ� -> ������Ʈ �� �ַ�� -> VC++ ���͸� -> �������� -> ������ JDK include ��� �߰�
// C:\Program Files (x86)\Java\jdk1.7.0_15\include
// C:\Program Files (x86)\Java\jdk1.7.0_15\include\win32
// �� �ڵ�� dll �� ����(���)�ϵ��� �����Ѵ�.
// �����Ӽ�->�Ϲ�->��������->���� ���̺귯�� (.dll) ����
// �����Ӽ�->��Ŀ->�Ϲ�->������ϸ�.dll
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
	// java Ÿ������ ����� �����Ͽ� ����
	jint sum;
	sum = a+b;
	return sum;
}
JNIEXPORT jstring JNICALL Java_com_Android_1ServerMon_JNIManager_PrintString(JNIEnv *env, jobject obj, jstring msg)
{
	printf("This C Java_JNIManager_PrintString()\n");
	// java �� 2����Ʈ(16��Ʈ) ���ڿ��� C �� 1����Ʈ(8��Ʈ) ���ڿ��� ��ȯ
	const char *szStr = env->GetStringUTFChars(msg, 0);

	printf("string from java : %s", szStr);
	char szBuffer[1024];
	memset(szBuffer, 0, sizeof(szBuffer));
	strcat(szBuffer, "Name: ");
	strcat(szBuffer, szStr);

	// JVM ���� ���ڿ� ����� �����ٰ� �˷��ְ� �޸� ����
	env->ReleaseStringUTFChars(msg, szStr);

	// C �� ��Ƽ����Ʈ ���ڿ��� java �� �����ڵ�� ��ȯ�Ͽ� ����
	return env->NewStringUTF(szBuffer);
}
