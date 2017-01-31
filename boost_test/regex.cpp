// ysoftman
// boost 정규식 사용하기
// 빌드시 boost_regex 링크
// g++ -lboost_regex regex.cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/foreach.hpp>

using namespace std;

int main()
{
	cout << "regex test" << endl;

	string url_param = "aa=aaa&bb=bbb&cc=123&dd=ddd";
	cout << "url_param: " << url_param << endl;

	// url 파라미터에서 특정 키 값 변경하기ㅏ
	// 변경할 키 정하기
	vector<string> keys;
	keys.push_back("bb");
	keys.push_back("cc");
	keys.push_back("zz");
 
	// 키값을 찾는 정규 표현식 만들기
	ostringstream regex_format;
	regex_format << "(";
	unsigned int i = 0;
	BOOST_FOREACH(string key, keys)
	{
		cout << "key: " << key << endl;
		// 참고 https://ko.wikipedia.org/wiki/%EC%A0%95%EA%B7%9C_%ED%91%9C%ED%98%84%EC%8B%9D
		// (key=  또는 &key= 로 시작하고) (& 로 가 아닌 것들이 1번이상 발생)
		regex_format << "^" << key << "\\=|\\&" << key << "\\=";
		
		if (++i < keys.size())
		{
			regex_format << "|";
		}
	}
	regex_format << ")([^\\&]+)";
	cout << "regex_format: " << regex_format.str() << endl;


	boost::regex re(regex_format.str());
	boost::smatch match;
	string url_param_replaced;
	// url 에서 정규 표현식으로 찾아 변경하기
	while (regex_search(url_param, match, re)) 
	{
		// 매칭되는 키 위치 이전 스트링
		cout << "match.prefix().str(): " << match.prefix().str() << endl;
		// 첫번째로 매칭되는 키 위치
		cout << "match[1]: " << match[1] << endl;
		// 매칭되는 키 위치 이후 스트링
		cout << "match.suffix().str(): " << match.suffix().str() << endl;
		// 매칭되는 키 뒤의 값은 무시하고 _ 로 대체
		url_param_replaced += match.prefix().str() + match[1] + "_";
		// 나머지 부분에서 계속 찾아 나간다.
		url_param = match.suffix().str();
	}
	cout << "replaced url param: " << url_param_replaced + url_param << endl;

	return 0;
}
