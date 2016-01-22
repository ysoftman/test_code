////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// JNI(Java Native Interface) �׽�Ʈ
// JNI(Java Native Interface) �� Java���� C �ڵ带 ����� �� �ִ�.
// JNIManager Ŭ������ ���� JNIManager.h ���� ����
// javah -jni JNIManager
////////////////////////////////////////////////////////////////////////////////////
class JNIManager {
	static {
		// C++ �� ���� .dll �� �ε��Ѵ�.
		// ����� .dll �ε忡�� ���� �߻���
		// 32bit java.exe �� ����Ͽ� �����ϵ��� �Ѵ�.
		// �ε� ��� 1 - ���� ���丮�� .dll ��ġ
		// System.loadLibrary("JNIImpl");
		// �ε� ��� 2 - ���� ��� ���
		System.load("D:\\ysoftman\\Project\\ysoftmanCode\\Debug\\JNIImpl.dll");
	}
	
	// �ܼ� ȣ��
	public native void Print();
	
	// int �ְ� �ޱ�
	public native int Add(int a, int b);
	
	// ���ڿ� �ְ� �ޱ�
	public native String PrintString(String str);
}

public class JNITest {
	public static void main(String[] args) {
		System.out.println("This java println");
		// JNI ����ϱ�
		JNIManager jni = new JNIManager();
		jni.Print();
		int c = jni.Add(1, 2);
		System.out.println("jni.Add(1, 2) retun " + c);
		String msg = jni.PrintString("YoonByoungHoon");
		System.out.println("jni.PrintString(\"YoonByoungHoon\") retun " + msg);
	}
}
