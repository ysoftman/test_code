////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// jsoncpp library �׽�Ʈ
// json ���� Ȩ������ http://json.org
// jsoncpp
// http://sourceforge.net/projects/jsoncpp/
// http://jsoncpp.sourceforge.net/ 
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <vector>

#include "json/json.h"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#if defined(_DEBUG)
#define JSON_DEBUG
#pragma comment(lib, "./json/json_vc71_libmtd")
#else
#pragma comment(lib, "./json/json_vc71_libmt")
#endif
#else // linux
#endif

string JsonWriteTest();
void JsonReadTest(string strJSON);

int main()
{
	string result = JsonWriteTest();
	JsonReadTest(result);

	return 0;
}

string JsonWriteTest()
{
	/*
	{
	"�̸�": "������",
	"����": 30,
	"ģ��": ["ȫ�浿", "�����ں���"],
	"����": "��"
	}
	*/
	// ���� ���� json ���� �����
	Json::Value root;
	root["�̸�"] = "������";
	root["����"] = 30;
	Json::Value friends;
	friends.append("ȫ�浿");
	friends.append("�����ں���");
	root["ģ�� ����Ʈ"] = friends;
	root["����"] = "��";

	Json::StyledWriter writer;
	string strJSON = writer.write(root);
	
	cout << "JSON WriteTest" << endl << strJSON << endl;

	return strJSON;
}

void JsonReadTest(string strJSON)
{
	// json ���� �б�
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(strJSON, root) == false)
	{
		cout << "JSON parsing failed." << endl;
		return;
	}

	cout << "JSON ReadTest" << endl;

	string name = root.get("�̸�", "defaultvalue").asString();
	cout << "�̸�: " << name << endl;
	
	int age = root.get("����", "defaultvalue").asInt();
	cout << "����: " << age << endl;

	Json::Value friends;
	friends = root["ģ�� ����Ʈ"];
	cout << "ģ�� ����Ʈ: " << endl;
	for (unsigned int i=0; i<friends.size(); ++i)
	{
		cout << friends[i].asString() << endl;
	}

	string sex = root.get("����", "defaultvalue").asString();
	cout << "����: " << sex << endl;
}

