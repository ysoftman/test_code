////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Call by Value , Call by Reference
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <vector>
#include <string>

int value(int a)
{
	printf ("%s\ta(%p)\n", __FUNCTION__, &a);
	a = a+5;
	return a;
}

void reference(int *a)
{
	printf ("%s\ta(%p)\n", __FUNCTION__, a);
	printf ("%s\t&a(%p)\n", __FUNCTION__, &a);
	*a = *a+5;
}

class Dummy
{
public:
	Dummy()
	{
		nVal = 0;
		strVal = "empty";
	}
	~Dummy(){};

	int nVal;
	std::string strVal;

};
void func1(std::vector<Dummy*> vecDum)
{
	std::vector<Dummy*>::iterator iter;
	int idx = 0;
	std::string str = "";
	for (iter = vecDum.begin(); iter != vecDum.end(); ++iter)
	{
		(*iter)->nVal = ++idx;
		str += "a";
		(*iter)->strVal = str;
		printf ("(*iter)->nVal = %d, (*iter)->strVal = %s\n", (*iter)->nVal, (*iter)->strVal.c_str());
	}

}
int main()
{
	int num = 5;
	printf ("num(%p)\n", &num);
	num = value(num);
	printf ("Call by Value : %d\n", num);
	reference(&num);
	printf ("Call by Reference : %d\n", num);
	int* pnum = &num;
	printf ("pnum(%p)\n", pnum);
	printf ("pnum(%p)\n", &pnum);
	reference(pnum);
	printf ("Call by Reference : %d\n", num);


	std::vector<Dummy*> vecDum;
	for (int i = 0; i<3; i++) 
	{
		Dummy *dum = new Dummy();
		vecDum.push_back(dum);
	}
	std::vector<Dummy*>::iterator iter;
	for (iter = vecDum.begin(); iter != vecDum.end(); ++iter)
	{
		printf ("(*iter)->nVal = %d, (*iter)->strVal = %s\n", (*iter)->nVal, (*iter)->strVal.c_str());
	}

	printf ("------------------------------\n");
	func1(vecDum);
	printf ("------------------------------\n");

	for (iter = vecDum.begin(); iter != vecDum.end(); ++iter)
	{
		printf ("(*iter)->nVal = %d, (*iter)->strVal = %s\n", (*iter)->nVal, (*iter)->strVal.c_str());
	}

	while(!vecDum.empty()){ delete vecDum.back(); vecDum.pop_back(); }

	return 0;
}
