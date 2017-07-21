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

string WriteJsonTest()
{
	cout << "testing... " << __FUNCTION__ << endl;
	/*
	{
	"a" : {
		"b" : "c"
	},
	"이름": "윤병훈",
	"나이": 30,
	"친구": ["홍길동", "엘리자베스"],
	"성별": "남"
	}
	*/
	// 위와 같은 json 문서 만들기
	Json::Value root;
	root["a"]["b"] = "c";
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

void ReadJsonTest(string strJSON)
{
	cout << "testing... " << __FUNCTION__ << endl;
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
	cout << "성별: " << sex << endl << endl;
}

void TraverseJsonTest(Json::Value root)
{
	cout << "testing... " << __FUNCTION__ << endl;
	Json::Value::Members members = root.getMemberNames();
	for (int i=0; i<(int)members.size(); i++)
	{
		Json::Value key = members[i];
		Json::Value value = root[key.asString()];
		cout << key.asString() << endl;
		if (value.isObject())
		{
			// object 는 재귀호출
			TraverseJsonTest(value);
		}
		else if (value.isString())
		{
			cout << value.asString() << endl;
		}
		else if (value.isInt())
		{
			cout << value.asInt() << endl;
		}			
	}	
}

int main()
{
	// json 쓰기
	string result = WriteJsonTest();
	// json 읽기
	ReadJsonTest(result);

	// json 탐색
	string strJSON = "{"
		"\"Info\":" 
		"{"
		"\"num1\":999,"
		"\"num2\":123456789,"
		"\"str1\":\"ysoftman\""
		"}"
		"}";
	cout << "strJSON = " << strJSON << endl;
	Json::Value root;
	Json::Reader reader;	
	if (reader.parse(strJSON, root) == true)
	{
		TraverseJsonTest(root);
	}

	return 0;
}
