////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// jsoncpp library 테스트
// json 공식 홈페이지 http://json.org
// jsoncpp
// http://sourceforge.net/projects/jsoncpp/
// http://jsoncpp.sourceforge.net/
// mac jsoncpp 설치
// brew install jsoncpp
// build
// g++ JsonCppTest.cpp -ljsoncpp
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>

#include <json/json.h>

using namespace std;

string JsonWriteTest();
void JsonReadTest(string strJSON);

int main()
{
	// 테스트1
	printf("test1---------------\n");
	string result = JsonWriteTest();
	JsonReadTest(result);


	// 테스트2
	printf("test2---------------\n");
	Json::Value root;
	Json::Reader reader;
	string strJSON = "{"
		"\"Info\":" 
		"{"
		"\"num1\":999,"
		"\"num2\":123456789,"
		"\"str1\":\"ysoftman\""
		"}"
		"}";
	printf("strJSON = %s\n", strJSON.c_str());
	if (reader.parse(strJSON, root) == true)
	{
		Json::Value info = root["Info"];
		if (info.isNull() == false)
		{
			int64_t num1 = info.get("num1",0).asInt();
			int64_t num2 = info.get("num2",0).asInt();
			string str1 = info.get("str1","").asString();
			printf("num1=%lld, num2=%lld, str1=%s\n", num1, num2, str1.c_str());
		}
	}

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

