////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// virtual Ű���� ��� ��
// public, protected, private Ű���� ��� ��
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

class Parent
{
public:
	virtual void public_func()
	{
		cout << "Parent public_func()\n";
	}
protected:
	void protected_func()
	{
		cout << "Parent protected_func()\n";
	}
private:
	void private_func()
	{
		cout << "Parent private_func()\n";
	}
};

class Child : public Parent	// public �� ������� ������ �⺻ private ���� ��ӵ�
{
public:
	void public_func()	// Parent public_func() �������̵�
	{
		cout << "Child public_func()\n";
	}
	void public_call_protected_func()
	{
		cout << "Child public_call_protected_func() --> ";
		protected_func();
	}

protected:
	void protected_func()
	{
		cout << "Child protected_func()\n";
	}
private:
	void private_func()
	{
		cout << "Child private_func()\n";
	}
};


int main()
{
	Parent *p = new Child();
	// Parent �� public_func() �� virtual �� ������ Child public_func() ȣ��
	// Parent �� public_func() �� virtual �� ������ Parent public_func() ȣ��
	p->public_func();
	delete p;


	Child *c = new Child();
	// Child �ν��Ͻ����� public �׼��� ����
	c->public_func();
	// Child �ν��Ͻ����� protected �׼��� �Ұ���
	// protected �� Child Ŭ���� �������� �׼��� ����
	//c->protected_func();
	c->public_call_protected_func();
	// Child �� private �׼��� �Ұ���
	//c->public_func3();
	delete c;

	return 0;
}

