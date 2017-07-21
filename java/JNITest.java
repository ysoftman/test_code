////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// JNI(Java Native Interface) 테스트
// JNI(Java Native Interface) 로 Java에서 C 코드를 사용할 수 있다.
// JNIManager 클래스로 부터 JNIManager.h 파일 생성
// javah -jni JNIManager
////////////////////////////////////////////////////////////////////////////////////
class JNIManager {
	static {
		// C++ 로 만든 .dll 를 로드한다.
		// 실행시 .dll 로드에서 에러 발생시
		// 32bit java.exe 를 사용하여 실행하도록 한다.
		// 로드 방법 1 - 같은 디렉토리에 .dll 위치
		// System.loadLibrary("JNIImpl");
		// 로드 방법 2 - 절대 경로 명시
		System.load("D:\\ysoftman\\Project\\ysoftmanCode\\Debug\\JNIImpl.dll");
	}
	
	// 단순 호출
	public native void Print();
	
	// int 주고 받기
	public native int Add(int a, int b);
	
	// 문자열 주고 받기
	public native String PrintString(String str);
}

public class JNITest {
	public static void main(String[] args) {
		System.out.println("This java println");
		// JNI 사용하기
		JNIManager jni = new JNIManager();
		jni.Print();
		int c = jni.Add(1, 2);
		System.out.println("jni.Add(1, 2) retun " + c);
		String msg = jni.PrintString("YoonByoungHoon");
		System.out.println("jni.PrintString(\"YoonByoungHoon\") retun " + msg);
	}
}
