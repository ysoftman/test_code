////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// string ��Ʈ�� ���� ù��° ����Ʈ�� \t \n \r �� Ư�������� ��� ������ ����
////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <ios>		// ios_base, ios
#include <istream>	// iostream, istream, ostream, streambuf
#include <iostream>	// cin, cout, cerr, clog
#include <fstream>	// ifstream, fstream, ofstream, filebuf
#include <sstream>	// istringstream, stringstream, ostringstream, stringbuf

using namespace std;

string getStringStream1(string str)
{
	string strResult;
	istringstream is(str);
	stringbuf strBuf;
	// ù��° ����Ʈ�� \t \n \r �� Ư�������� ��� ����� ��µ��� �ʴ´�.
	is >> &strBuf;
	strResult = strBuf.str();
	return strResult;
}

string getStringStream2(string str)
{
	string strResult;
	istringstream iss(str);
	// ��� ��Ʈ���� ���������� ����Ѵ�.
	iss.seekg(0, iss.end);
	int size = (int)iss.tellg();
	iss.seekg(0, iss.beg);
	if (size > 0)
	{
		char *buf = new char[size];
		iss.read(buf, size);
		strResult.assign(buf, size);
		delete [] buf;
	}
	return strResult;
}

int main()
{
	__int32 llMsgID = 231520362;
	string strIn;
	string strOut;
	
	// ������ ���� ���
	char szBuffer[5];
	memset(szBuffer, 0, sizeof(szBuffer));
	memcpy(szBuffer, &llMsgID, sizeof(llMsgID));
	strIn = szBuffer;
	cout << "in :";
	for (unsigned int i=0; i<strIn.size(); ++i)
	{
		cout << (int)strIn[i] << "  ";
	}
	cout << endl;
	strOut = getStringStream1(strIn);

	cout << "out: ";
	for (unsigned int i=0; i<strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;
	cout << endl;
	cout << endl;

	// \t \n \r ������ ���۵Ǵ� ��� stirng ��Ʈ���� >> ���� ù��° ����Ʈ�� ������ ���� �߻�
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
	for (unsigned int i=0; i<strIn.size(); ++i)
	{
		cout << (int)strIn[i] << "  ";
	}
	cout << endl;
	strOut = getStringStream1(strIn);		// ù��° ����Ʈ ���ܵ�
	cout << "out: ";
	for (unsigned int i=0; i<strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;

	strOut = getStringStream2(strIn);		// ��� ��Ʈ�� ����
	cout << "out: ";
	for (unsigned int i=0; i<strOut.size(); ++i)
	{
		cout << (int)strOut[i] << "  ";
	}
	cout << endl;

	return 0;
}

