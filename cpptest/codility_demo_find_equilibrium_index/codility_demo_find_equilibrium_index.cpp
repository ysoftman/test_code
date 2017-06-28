// title : find_equilibrium_index
// author : ysoftman
// 문제 : https://codility.com/c/run/demo23NSFC-WFE
// 결과 : https://codility.com/demo/results/demo5WNNRP-Y8T
// codility 데모 테스트 풀기

#include <stdio.h>
#include <vector>

using namespace std;

// 주어진 정수 배열에서 앞부분에서의 합과 뒷부분에서의 합이 같아 기즌 지점(equilibrium index) 찾기
// 여러개의 equilibrium index 가 있을 수 있기 때문에 결과 값을 배열로 따로 받는다.
int solution(vector<int> &A, vector<int> &output) {
	// write your code in C++11 (g++ 4.8.2)
	long prefix_sum = 0;
	long surfix_sum = 0;

	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	for (i=0; i<A.size();i++) {

		prefix_sum = surfix_sum = 0;
		for (j=0; j<i; j++) {
			prefix_sum += A[j];
		}

		for (k=i+1; k<A.size(); k++) {
			surfix_sum += A[k];
		}

		if (prefix_sum == surfix_sum) {
			//return i;
			output.push_back(i);
		}
	}

	return 0;
}

int main()
{
	vector<int> vecData;
	vector<int> vecResult;
	vecData.push_back(-1);
	vecData.push_back(3);
	vecData.push_back(-4);
	vecData.push_back( 5);
	vecData.push_back( 1);
	vecData.push_back(-6);
	vecData.push_back( 2);
	vecData.push_back( 1);

	// equilibrium index = 1, 3, 7
	solution(vecData, vecResult);

	vector<int>::iterator iter;
	for (iter=vecResult.begin(); iter!=vecResult.end(); iter++)
	{
		printf("equilibrium = %d\n", *iter);
	}


	vecData.clear();
}

