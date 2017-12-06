// ysoftman
// boost any 사용하기
#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>

using namespace std;
using namespace boost; 

int main()
{
    cout << "boost any test" << endl;

	// any 를 사용하면 javascript var변수와 같이 다양한 타입의 값을 저장할 수 있다.
	any anybuffer;
	// 저장된 값은 any_cast 로 타입렬로 접근할 수 있다.
	try {
		anybuffer = 123;
		cout << any_cast<int>(anybuffer) << endl;
		
		anybuffer = 0.123;
		cout << any_cast<double>(anybuffer) << endl;

		// 예외 발생
		// anybuffer = "ysoftman";
		// any 에 저장될 값은 copy-constructible 여야 한다.
		// 문자열은 string 형으로 담아야 한다.
		anybuffer = string("ysoftman");	
		cout << std::boolalpha << any_cast<string>(anybuffer) << endl;

		anybuffer = true;
		cout << std::boolalpha << any_cast<bool>(anybuffer) << endl;
	}
	catch (bad_any_cast &e) {
		// 실패시 bad_any_cast 예외 발생
		cout << e.what() << endl;
	}

	// 타입이 다른 값들을 벡터로 저장 출력해보기 
	vector<any> vecAny;
	vector<any>::iterator iter;
	vecAny.push_back(99999);
	vecAny.push_back(string("aaa"));
	vecAny.push_back(0.777);

	for (iter = vecAny.begin(); iter != vecAny.end(); iter++)
	{
		if ((*iter).type().name() == typeid(int).name())
		{
			cout << any_cast<int>(*iter) << endl;
		}
		else if ((*iter).type().name() == typeid(string).name())
		{
			cout << any_cast<string>(*iter) << endl;
		}
 		else if ((*iter).type().name() == typeid(double).name())
		{
			cout << any_cast<double>(*iter) << endl;
		}
	}

    return 0;
}
