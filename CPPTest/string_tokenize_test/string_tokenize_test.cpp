////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���ڿ� ��ū������
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//str				�Ľ��� ���ڿ�
//tokens			��ū�� ���� ����
//delimiter			������
void StringTokenize(string str, vector<string> &tokens, string delimiter)
{
	// ó�� �����ڰ� ��������� ����ؼ�
	// find_first_not_of �� offset ���� �����ڰ� �ƴ� ���ڰ� ó�� ���� ���� ã�´�.
	string::size_type frompos = str.find_first_not_of(delimiter, 0);
	string::size_type topos = str.find_first_of(delimiter, frompos);
	while (topos != string::npos)
	{
		// substr(offset, count) 
		tokens.push_back(str.substr(frompos, topos-frompos));
		frompos = str.find_first_not_of(delimiter, topos);
		topos = str.find_first_of(delimiter, frompos);		
	}
	// �������� �����ڰ� �������� ��������� frompos ���� �������� �ϳ��� ��ū�� ����.
	if (frompos != string::npos)
	{
		tokens.push_back(str.substr(frompos, topos-frompos));
	}
}

int main()
{
	string strTest = "����,�ٶ󸶹�,�����,��īŸ��,��";
	cout << strTest << endl;
	vector<string> vecTokens;
	vector<string>::iterator iter;
	StringTokenize(strTest, vecTokens, ",");
	for (iter = vecTokens.begin(); iter != vecTokens.end(); ++iter)
	{
		cout << (*iter).c_str() << endl;
	}
	return 0;
}


