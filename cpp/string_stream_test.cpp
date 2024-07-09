// ysoftman
// string 스트림 사용시 첫번째 바이트가 \t \n \r 등 특수문자인 경우 빠지는 문제
#include <string>
#include <ios>		// ios_base, ios
#include <istream>  // iostream, istream, ostream, streambuf
#include <iostream> // cin, cout, cerr, clog
#include <fstream>  // ifstream, fstream, ofstream, filebuf
#include <sstream>  // istringstream, stringstream, ostringstream, stringbuf

using namespace std;

string getStringStream1(string str)
{
	string strResult;
	istringstream is(str);
	stringbuf strBuf;
	// 첫번째 바이트가 \t \n \r 등 특수문자인 경우 제대로 출력되지 않는다.
	is >> &strBuf;
	strResult = strBuf.str();
	return strResult;
}

string getStringStream2(string str)
{
	string strResult;
	istringstream iss(str);
	// 모든 스트림을 정상적으로 출력한다.
	iss.seekg(0, iss.end);
	int size = (int)iss.tellg();
	iss.seekg(0, iss.beg);
	if (size > 0)
	{
		char *buf = new char[size];
		iss.read(buf, size);
		strResult.assign(buf, size);
		delete[] buf;
	}
	return strResult;
}

void tokenize_using_istringstream()
{
	cout << "[tokenize using istream]" << endl;
	string str = "1.23 z 3.45 ysoftman";
	cout << "str: " << str << endl;
	float a;
	char b;
	float c;
	string d;
	// 문자열에서 타입에 맞게 값을 토크나이즈 할 수 있다.
	istringstream iss(str);
	iss >> a >> b >> c >> d;
	cout << "a(float): " << a << endl;
	cout << "b(char): " << b << endl;
	cout << "c(float): " << c << endl;
	cout << "d(string): " << d << endl;
	cout << endl;
	cout << endl;
}

int main()
{
	tokenize_using_istringstream();

	cout << "[\\t \\n \\r string stream operator >> omit first byte]" << endl;
	int llMsgID = 231520362;
	string strIn;
	string strOut;

	// 문제가 없는 경우
	char szBuffer[5];
	memset(szBuffer, 0, sizeof(szBuffer));
	memcpy(szBuffer, &llMsgID, sizeof(llMsgID));
	strIn = szBuffer;
	cout << "in :";
	for (unsigned int i = 0; i < strIn.size(); ++i)
	{
		cout << (int)strIn[i] << "  ";
	}
	cout << endl;
	strOut = getStringStream1(strIn);

	cout << "out: ";
	for (unsigned int i = 0; i < strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;

	// \t \n \r 등으로 시작되는 경우 string 스트림의 >> 사용시 첫번째 바이트가 빠지는 문제 발생
	char szBuffer2[5];
	memset(szBuffer2, 0, sizeof(szBuffer2));
	//szBuffer2[0] = '\t';
	//szBuffer2[0] = '\n';
	//szBuffer2[0] = '\r';
	szBuffer2[0] = szBuffer[3];
	szBuffer2[1] = szBuffer[2];
	szBuffer2[2] = szBuffer[1];
	szBuffer2[3] = szBuffer[0];
	strIn = szBuffer2;
	cout << "in :";
	for (unsigned int i = 0; i < strIn.size(); ++i)
	{
		cout << (int)strIn[i] << "  ";
	}
	cout << endl;
	strOut = getStringStream1(strIn); // 첫번째 바이트 제외됨
	cout << "out: ";
	for (unsigned int i = 0; i < strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;

	strOut = getStringStream2(strIn); // 모든 스트림 복사
	cout << "out: ";
	for (unsigned int i = 0; i < strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;

	return 0;
}
