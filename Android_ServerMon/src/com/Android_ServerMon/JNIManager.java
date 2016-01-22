package com.Android_ServerMon;

////////////////////////////////////////////////////////////////////////////////////
//ysoftman
//NDK(Native Development Kit) �� Android ȯ�濡�� JNI ����� ����� �� �ְ� �Ѵ�.
//�⺻���� ������ ������� JNI �� ���� �߰��� Native �ڵ尡 Android ȯ�濡�� ����Ǿ�� �Ѵ�.
//JNIManager.h ���� ����
//javah -jni JNIManager
////////////////////////////////////////////////////////////////////////////////////
class JNIManager {
	static {
		// C++ �� ���� .dll �� �ε��Ѵ�.
		// ����� .dll �ε忡�� ���� �߻���
		// 32bit java.exe �� ����Ͽ� �����ϵ��� �Ѵ�.
		
		// �ε� ��� 1 - ���� ���丮�� .dll (.so �� ��� �����̸����� lib �� ����) ��ġ
		System.loadLibrary("JNIImpl");
		// �ε� ��� 2 - ���� ��� ���
		// System.load("libs/armeabi/libJNIImpl.so");
	}
	
	// �ܼ� ȣ��
	public native void Print();
	
	// int �ְ� �ޱ�
	public native int Add(int a, int b);
	
	// ���ڿ� �ְ� �ޱ�
	public native String PrintString(String str);
}
