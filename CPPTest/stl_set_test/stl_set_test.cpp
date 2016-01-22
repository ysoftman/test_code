////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// STL set
// Standard Template Library(STL) -> ���÷����� �̷���� Ŭ������ �Լ��� ���� ���̺귯��
// STL�� ������ �����̳�, �˰���, �ݺ���
// �����̳� ==> vector,list,string ,set,map,queue,priority_queue,stack,multiset,multimap ...
// �˰��� ==> sort() ,begin() ...
// �ݺ���   ==> �ݺ���(iterator)��, �����̳ʿ� ����Ǿ� �ִ� ��� ���ҵ��� ��ü������
//				�Ⱦ�� �� ����ϴ�, ������ �����Ϳ� ����� ��ü
////////////////////////////////////////////////////////////////////////////////////
// Example 1
#include <iostream>
#include <set>
#include <string>

// set�� ����ϱ� ���� std ���ӽ����̽� ���, std���� cout, cin, endl.. ���� �ִ�.
using namespace std;

int main()
{
	// set�� ����Ǵ� �׸���� ���������� �������ش�.
	//��������
	set<int, less<int> > s;
	set<int, less<int> >::iterator i;
	
	s.insert(4);
	s.insert(0);
	s.insert(-9);
	s.insert(7);
	s.insert(-2);
	s.insert(4);
	s.insert(2);
	
	cout << "The set contains the elements: ";

	for (i=s.begin(); i!=s.end(); i++)
	{
		cout << *i << ' ';
	}

	cout << endl;

	return 0;
}

