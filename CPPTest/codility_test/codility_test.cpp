#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

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


void StringTokenize(string str, vector<string> &tokens, string delimiter)
{
	string::size_type frompos = str.find_first_not_of(delimiter, 0);
	string::size_type topos = str.find_first_of(delimiter, frompos);

	while (topos != string::npos)
	{
		// substr(offset, count) 
		tokens.push_back(str.substr(frompos, topos-frompos));
		frompos = str.find_first_not_of(delimiter, topos);
		topos = str.find_first_of(delimiter, frompos);		
	}

	if (frompos != string::npos)
	{
		tokens.push_back(str.substr(frompos, topos-frompos));
	}
}

int solution2(int N, string &S) {
	// write your code in C++11 (g++ 4.8.2)
	
	int *pSeat = new int(10*N);
	memset(pSeat, 0, sizeof(int)*10*N);
	vector<string> vecString;
	StringTokenize(S, vecString, " ");

	vector<string>::iterator iter;
	for (iter = vecString.begin(); iter != vecString.end(); iter++)
	{
		int row = atoi((*iter).c_str()) - 1;
		int col = 0;
		if ( *(iter+1) == "A") {
			col = 0;
		}
		else if ( *(iter+1) == "B") {
			col = 1;
		}
		else if ( *(iter+1) == "C") {
			col = 2;
		}

		else if ( *(iter+1) == "D") {
			col = 3;
		}
		else if ( *(iter+1) == "E") {
			col = 4;
		}
		else if ( *(iter+1) == "F") {
			col = 5;
		}
		else if ( *(iter+1) == "G") {
			col = 6;
		}

		else if ( *(iter+1) == "H") {
			col = 7;
		}
		else if ( *(iter+1) == "J") {
			col = 8;
		}
		else if ( *(iter+1) == "K") {
			col = 9;
		}

		pSeat[row*10+col] = 1;

	}

	/// do something


	delete pSeat;
	

	return 0;
}


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

int main() {

	vector<int> vec;
	vec.push_back(4);
	vec.push_back(6);
	vec.push_back(2);
	vec.push_back(2);
	vec.push_back(6);
	vec.push_back(6);
	vec.push_back(4);

	printf("%d\n", solution4(vec));


	string str = "ABBCC";

	printf("%s\n", solution3(str).c_str());


	string input = "1A 2F 1C";
	printf("%s\n", solution2(2, input));


	int a = 213;
	printf("%d\n", solution1(a));
	a = 535;
	printf("%d\n", solution1(a));
}
