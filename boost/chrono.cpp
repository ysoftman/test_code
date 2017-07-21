// ysoftman
// boost chrono 사용하기
// 빌드시 boost_system boost_chrono 링크
// g++ -lboost_system -lboost_chrono chrono.cpp
#include <iostream>
#include <boost/chrono.hpp>

using namespace std;
using namespace boost::chrono; 

int main()
{
    cout << "chrono test" << endl;

	// 경과시간 측정
	system_clock::time_point start = system_clock::now();
	float ff = 12.12;
	for (int i=0; i<1000000; i++)
	{
		ff *= ff;
	}
	system_clock::time_point end = system_clock::now();
	// 초 단위 측정
	seconds sdiff = duration_cast<seconds>(end - start);
	// 마이크로 초 단위 측정
	microseconds msdiff = duration_cast<milliseconds>(end - start);
	// 나노 초 단위 측정
	nanoseconds nsdiff = duration_cast<microseconds>(end - start);
	cout << "elapsed : " << sdiff << endl;
	cout << "elapsed : " << msdiff << endl;
	cout << "elapsed : " << nsdiff << endl;

    return 0;
}
