////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// virtual 키워드 사용 예
// public, protected, private 키워드 사용 예
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

class Child : public Parent	// public 을 사용하지 않으면 기본 private 으로 상속됨
{
public:
	void public_func()	// Parent public_func() 오버라이딩
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
	// Parent 의 public_func() 에 virtual 이 있으면 Child public_func() 호출
	// Parent 의 public_func() 에 virtual 이 없으면 Parent public_func() 호출
	p->public_func();
	delete p;


	Child *c = new Child();
	// Child 인스턴스에서 public 액세스 가능
	c->public_func();
	// Child 인스턴스에서 protected 액세스 불가능
	// protected 는 Child 클래스 내에서만 액세스 가능
	//c->protected_func();
	c->public_call_protected_func();
	// Child 의 private 액세스 불가능
	//c->public_func3();
	delete c;

	return 0;
}
