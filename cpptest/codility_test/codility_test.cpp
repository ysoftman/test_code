#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;


int solution1(int N) {
	// write your code in C++11 (g++ 4.8.2)
	vector<int> vecTemp;
	while (N/10 > 0)
	{
		vecTemp.push_back(N%10);
		N /= 10;
	}
	vecTemp.push_back(N);

	// sort
	vector<int>::iterator iter;
	vector<int>::iterator iter2;
	int n = 0;
	for (iter = vecTemp.begin(); iter != vecTemp.end(); iter++) {
		for (iter2 = vecTemp.begin(); iter2 != vecTemp.end()-1; iter2++) {
			if (*iter2 < *(iter2+1))
			{
				n = *iter2;
				*iter2 = *(iter2+1);
				*(iter2+1) = n;
			}
		}
	}

	int nResult = 0;
	for (iter = vecTemp.begin(); iter != vecTemp.end(); iter++) 
	{
		nResult = (nResult * 10) + *iter;
	}
	return nResult;

}



int solution2(int N, string &S) {
	// write your code in C++11 (g++ 4.8.2)
	int *pSeat = new int[3*N];
	memset(pSeat, 0, sizeof(int)*3*N);

	string::iterator iter;
	for (iter = S.begin(); iter != S.end(); iter++)
	{
		string str = &(*iter);

		if (str[0] == ' ') {
			continue;
		}
		int row = atoi(&str[0]) - 1;
		int col = 0;
		if ( str[1] >= 'A' && str[1] <= 'C') {
			col = 0;
		}

		else if ( str[1] >= 'D' && str[1] <= 'G') {
			col = 1;
		}

		else if ( str[1] >= 'H' && str[1] <= 'K') {
			col = 2;
		}

		if (row < N && col < 3) {
			pSeat[row*3+col] = 1;
		}

		iter++;

	}

	/// do something
	int cnt = 0;
	for (int i=0; i<3*N; i++) {
		if (pSeat[i] == 1) {
			cnt++;
		}
	}
	
	delete pSeat;

	return (3*N) - cnt;
}



string solution3(string &S) {
	while (1) 
	{
		string str;
		str = S;
		// write your code in C++11 (g++ 4.8.2)
		for (unsigned int i=0; i<S.length()-1; i++) {
			string temp;
			temp += S[i];
			temp += S[i+1];
			if (temp == "AB") {
				S[i] = 'A';
				S[i+1] = 'A';

			}
			else if (temp == "BA") {
				S[i] = 'A';
				S[i+1] = 'A';

			}
			else if (temp == "CB") {
				S[i] = 'C';
				S[i+1] = 'C';

			}
			else if (temp == "BC") {
				S[i] = 'C';
				S[i+1] = 'C';

			}
			else if (temp == "AA") {
				S[i] = 'A';
				S.erase(i+1,1);
			}
			else if (temp == "CC") {
				S[i] = 'C';
				S.erase(i+1,1);
			}
			else
			{

			}
		}

		if (str == S)
		{
			break;
		}
	}
	return S;
}


int solution4(vector<int> &A) {
	int N = A.size();
	int result = 0;

	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		cnt++;
		printf("result:%d\n", result);
		if ((N-1)-i > result)
		{
			for (int j = N-1; j > i; j--)
			{
				cnt++;
				if (A[i] != A[j])
				{
					result = max(result, j - i);
					break;
				}

			}
		}
		else
		{
			break;
		}
	}


	printf("N:%d   cnt:%d\n", N, cnt);
	return result;
}


int main() {

	printf("solution1-----------------\n");
	int a = 213;
	printf("%d\n", solution1(a));
	a = 535;
	printf("%d\n", solution1(a));




	printf("solution2-----------------\n");
	string input = "1A 2F 1C";
	printf("%d\n", solution2(2, input));

	input = "1A 2F 1K";
	printf("%d\n", solution2(2, input));
	
	input = "";
	printf("%d\n", solution2(2, input));




	printf("solution3-----------------\n");
	string str = "ABBCC";
	printf("%s\n", solution3(str).c_str());



	printf("solution4-----------------\n");
	vector<int> vec;
	vec.push_back(4);
	vec.push_back(6);
	vec.push_back(2);
	vec.push_back(2);
	vec.push_back(6);
	vec.push_back(6);
	vec.push_back(4);

	printf("%d\n", solution4(vec));

}
