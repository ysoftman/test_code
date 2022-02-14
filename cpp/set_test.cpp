// ysoftman
// STL set
// Standard Template Library(STL) -> 템플렛으로 이루어진 클래스나 함수의 모음 라이브러리
// STL의 구성은 컨테이너, 알고리즘, 반복자
// 컨테이너 ==> vector,list,string ,set,map,queue,priority_queue,stack,multiset,multimap ...
// 알고리즘 ==> sort() ,begin() ...
// 반복자   ==> 반복자(iterator)란, 컨테이너에 저장되어 있는 모든 원소들을 전체적으로
//				훑어나갈 때 사용하는, 일종의 포인터와 비슷한 객체
// Example 1
#include <iostream>
#include <set>
#include <string>

// set을 사용하기 전에 std 네임스페이스 사용, std에는 cout, cin, endl.. 등이 있다.
using namespace std;

int main()
{
	// set은 저장되는 항목들을 내부적으로 정렬해준다.
	//내림차순
	set<int, less<int> > s;
	set<int, less<int> >::iterator i;

	s.insert(4);
	s.insert(0);
	s.insert(-9);
	s.insert(7);
	s.insert(-2);
	s.insert(4);	// 중복된 값은 하나로 취급
	s.insert(2);

	cout << "The set contains the elements: ";

	for (i = s.begin(); i != s.end(); i++)
	{
		cout << *i << ' ';
	}

	cout << endl;

	return 0;
}
