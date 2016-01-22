////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// jsoncpp library 테스트
// json 공식 홈페이지 http://json.org
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
	"이름": "윤병훈",
	"나이": 30,
	"친구": ["홍길동", "엘리자베스"],
	"성별": "남"
	}
	*/
	// 위와 같은 json 문서 만들기
	Json::Value root;
	root["이름"] = "윤병훈";
	root["나이"] = 30;
	Json::Value friends;
	friends.append("홍길동");
	friends.append("엘리자베스");
	root["친구 리스트"] = friends;
	root["성별"] = "남";

	Json::StyledWriter writer;
	string strJSON = writer.write(root);
	
	cout << "JSON WriteTest" << endl << strJSON << endl;

	return strJSON;
}

void JsonReadTest(string strJSON)
{
	// json 문서 읽기
	Json::Value root;
	Json::Reader reader;
	if (reader.parse(strJSON, root) == false)
	{
		cout << "JSON parsing failed." << endl;
		return;
	}

	cout << "JSON ReadTest" << endl;

	string name = root.get("이름", "defaultvalue").asString();
	cout << "이름: " << name << endl;
	
	int age = root.get("나이", "defaultvalue").asInt();
	cout << "나이: " << age << endl;

	Json::Value friends;
	friends = root["친구 리스트"];
	cout << "친구 리스트: " << endl;
	for (unsigned int i=0; i<friends.size(); ++i)
	{
		cout << friends[i].asString() << endl;
	}

	string sex = root.get("성별", "defaultvalue").asString();
	cout << "성별: " << sex << endl;
}

