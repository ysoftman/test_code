package com.Android_ServerMon;

////////////////////////////////////////////////////////////////////////////////////
//ysoftman
//NDK(Native Development Kit) 는 Android 환경에서 JNI 기술을 사용할 수 있게 한다.
//기본적인 원리와 사용방법은 JNI 와 같고 추가로 Native 코드가 Android 환경에서 빌드되어야 한다.
//JNIManager.h 파일 생성
//javah -jni JNIManager
////////////////////////////////////////////////////////////////////////////////////
class JNIManager {
	static {
		// C++ 로 만든 .dll 를 로드한다.
		// 실행시 .dll 로드에서 에러 발생시
		// 32bit java.exe 를 사용하여 실행하도록 한다.
		
		// 로드 방법 1 - 같은 디렉토리에 .dll (.so 일 경우 파일이름에서 lib 는 뺄것) 위치
		System.loadLibrary("JNIImpl");
		// 로드 방법 2 - 절대 경로 명시
		// System.load("libs/armeabi/libJNIImpl.so");
	}
	
	// 단순 호출
	public native void Print();
	
	// int 주고 받기
	public native int Add(int a, int b);
	
	// 문자열 주고 받기
	public native String PrintString(String str);
}
