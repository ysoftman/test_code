// ysoftman
// jsoncpp library 테스트 (1.8.3 기준)
// https://github.com/open-source-parsers/jsoncpp
// mac jsoncpp 설치
// brew install jsoncpp
// brew upgrade jsoncpp
// build
// g++ -std=c++11 ./jsoncpp.cpp -ljsoncpp && ./a.out

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <json/json.h>

using namespace std;

bool ul_isMember(Json::Value v, string key)
{
	string uk = key;
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	std::transform(uk.begin(), uk.end(), uk.begin(), ::toupper);
	if (v.isMember(key) || v.isMember(uk))
	{
		return true;
	}
	return false;
}

string WriteJson()
{
	cout << "testing... " << __FUNCTION__ << endl;
	/*
	{
	"a" : {
		"b" : "c"
	},
	"float_value" : 0.12346,
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
	root["float_value"] = 0.123456789123456789;
	root["float_value2"] = 0.00001;
	Json::Value friends;
	friends.append("홍길동");
	friends.append("엘리자베스");
	root["친구"] = friends;
	root["성별"] = "남";

	string strJSON;

	// StyledWriter deprecated
	// Json::StyledWriter writer;
	// strJSON = writer.write(root);
	// cout << "JSON Write" << endl
	// 	 << strJSON << endl;

	// 소수점등 기타 옵션 설정하여 스트링을 출력시 StreamWriterBuilder 사용
	Json::StreamWriterBuilder sb;
	// "None" or "All"
	sb["commentStyle"] = "None";
	sb["indentation"] = "\t";
	sb["enableYAMLCompatibility"] = false;
	sb["dropNullPlaceholders"] = false;
	sb["useSpecialFloats"] = false;
	// 소수점 x 자리까지만 설정(반올림된다.)
	sb["precision"] = 5;
	strJSON = Json::writeString(sb, root);

	cout << "JSON StreamWriteBuilder" << endl
		 << strJSON << endl;

	cout << "root.isMember(\"a\") : " << root.isMember("a") << endl;
	cout << "root.isMember(\"aa\") : " << root.isMember("aa") << endl;
	cout << "root.isMember(\"친구\") : " << root.isMember("친구") << endl;
	cout << "root.isMember(\"float_value\") : " << root.isMember("float_value") << endl;
	cout << "root.isMember(\"FLOAT_VALUE\") : " << root.isMember("FLOAT_VALUE") << endl;
	cout << "ul_isMember(root, \"float_Value\") : " << ul_isMember(root, "float_Value") << endl;
	cout << "ul_isMember(root, \"float_value\") : " << ul_isMember(root, "float_value") << endl;
	cout << "ul_isMember(root, \"FLOAT_VALUE\") : " << ul_isMember(root, "FLOAT_VALUE") << endl;

	return strJSON;
}

void ReadJson(string strJSON)
{
	cout << "testing... " << __FUNCTION__ << endl;
	// json 문서 읽기
	Json::Value root;

	// Reader deprecated.
	// Json::Reader reader;
	// if (reader.parse(strJSON, root) == false)
	// {
	// 	cout << "JSON parsing failed." << endl;
	// 	return;
	// }
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	std::istringstream strjson;
	strjson.str(strJSON);
	JSONCPP_STRING errs;
	bool ok = Json::parseFromStream(builder, strjson, &root, &errs);

	cout << "JSON Read" << endl;

	string name = root.get("이름", "defaultvalue").asString();
	cout << "이름: " << name << endl;

	int age = root.get("나이", "defaultvalue").asInt();
	cout << "나이: " << age << endl;

	// Value 값 변경
	Json::Value ageValue = root.get("나이", "defaultvalue").asInt();
	ageValue = ageValue.asInt() - 5;
	cout << "나이: " << ageValue.asInt() << endl;

	if (root["a"].isObject())
	{
		cout << "a isObject" << endl;
	}
	// 없는 필드를 오브젝트로 가져오기
	if (root["zzz"].isObject())
	{
		cout << "a isObject" << endl;
	}
	else
	{
		cout << "zzz is not exist field" << endl;
	}

	Json::Value friends;
	friends = root["친구"];
	if (friends.isArray())
	{
		cout << "친구 isArray" << endl;
	}
	cout << "친구: " << endl;
	for (unsigned int i = 0; i < friends.size(); ++i)
	{
		cout << friends[i].asString() << endl;
	}

	string sex = root.get("성별", "defaultvalue").asString();
	cout << "성별: " << sex << endl;

	// 없는 필드 체크
	string zzz = root.get("zzz", "defaultvalue").asString();
	cout << "zzz: " << zzz << endl;
	zzz = root["zzz"].asString();
	if (zzz == "")
	{
		cout << "zzz is not exist field" << endl;
	}

	cout << endl;
}

void TraverseJson(Json::Value root)
{
	cout << "testing... " << __FUNCTION__ << endl;
	Json::Value::Members members = root.getMemberNames();
	for (int i = 0; i < (int)members.size(); i++)
	{
		Json::Value key = members[i];
		Json::Value value = root[key.asString()];
		cout << key.asString() << endl;
		if (value.isObject())
		{
			// object 는 재귀호출
			TraverseJson(value);
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
	string result = WriteJson();
	// json 읽기
	ReadJson(result);

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

	// Reader deprecated.
	// Json::Reader reader;
	// if (reader.parse(strJSON, root) == true)
	// {
	// 	TraverseJson(root);
	// }
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	std::istringstream strjson;
	strjson.str(strJSON);
	JSONCPP_STRING errs;
	if (Json::parseFromStream(builder, strjson, &root, &errs))
	{
		TraverseJson(root);
	}

	return 0;
}
