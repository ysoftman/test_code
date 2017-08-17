////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Calculate Factorial
// Factorial Number Range : 0 ~ 16
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

//Using Recursive Function To Get Factorial.
int Fact_method1(int input)
{
	int output = 1;
	// 0! = 1 and 1! = 1
	if (input == 1 || input == 0)
	{
		output = 1;
		return output;
	}
	else
	{
		output = input * Fact_method1(input-1);
		return output;
	}
}
//Using Iteration Function To Get Factorial.
int Fact_method2(int input)
{
	int output = 1;
	while (input > 1)
	{
		output *= input;
		input--;
	}
	return output;
}

void main()
{
	unsigned int result=0;
	unsigned int in_number=0;
	printf ("[Factorial]Input Number : ");
	scanf("%d", &in_number);
	result = Fact_method1(in_number);
	printf ("recursive method %d! = %d\n", in_number, result);
	result = Fact_method2(in_number);
	printf ("iteration method %d! = %d\n", in_number, result);
}


