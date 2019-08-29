// ysoftman
// virtual 키워드 사용 예
// public, protected, private 키워드 사용 예
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
	void parent_protected_func()
	{
		cout << "Parent protected_func()\n";
	}

private:
	void parent_private_func()
	{
		cout << "Parent private_func()\n";
	}
};

// public 상속 : 부모의 public, protected, private 그대로 사용
// protected 상속 : 부모의 public -> protected 로 변경해 사용
// private 상속 : 부모의 public, protected -> private 로 변경해 사용
// public 을 사용하지 않으면 기본 private 으로 상속됨
class Child : public Parent
{
public:
	void public_func() // Parent public_func() 오버라이딩
	{
		cout << "Child public_func()\n";
		// 상속된 Child 클래스내에서 Parent protected 접근 가능
		parent_protected_func();
		// 상속된 Child 클래스내에서 Parent private 접근 불가능
		// parent_pravite_func();
	}
	void public_call_protected_func()
	{
		cout << "Child public_call_protected_func() --> ";
		protected_func();
		cout << "Child public_call_protected_func() --> ";
		private_func();
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

	// Child 클래스밖(인스턴스)에서 protected 액세스 불가능
	// c->protected_func();
	c->public_call_protected_func();

	// Child 클래스밖(인스턴스)에서 private 액세스 불가능
	//c->public_func3();
	delete c;

	return 0;
}
