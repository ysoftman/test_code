////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Dijkstra (다익스트라) 알고리즘으로 최단경로 찾기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stack>

const int X = 99999;	// 무한대
const int NUM_OF_NODES = 9;	// 노드 수
int Dijkstra(int N, int Matrix[NUM_OF_NODES][NUM_OF_NODES], int nStartPos, int Distance[], int PreNode[])
{
	if (nStartPos < 0 || nStartPos >= N)
	{
		return -1;
	}


	bool bFind[NUM_OF_NODES];
	for (int i=0; i<N; i++)
	{
		Distance[i] = X;
		bFind[i] = false;
		PreNode[i] = 0;
	}

	Distance[nStartPos] = 0;
	for (;;)
	{
		int min = X;
		int i = -1;

		for (int j=0; j<N; j++)
		{
			if (bFind[j] == false && Distance[j] < min)
			{
				min = Distance[j];
				i = j;
			}
		}
		// 더이상 탐색할 노드가 없다면 끝낸다.
		if (i == -1)
		{
			break;
		}
		bFind[i] = true;
		for (int j=0; j<N; j++)
		{
			// 현재 노드에 현재 노드까지의 비용중 가장 작은 비용합산으로 기록한다.
			if (Matrix[i][j] != X && Distance[j] > Distance[i] + Matrix[i][j])
			{
				Distance[j] = Distance[i] + Matrix[i][j];
				// 이전 노드 기록
				PreNode[j] = i;
			}
		}
	}
	return 0;
}
char *GetNodeName(int num)
{
	switch (num)
	{
	case 0:		return "A";
	case 1:		return "B";
	case 2:		return "C";
	case 3:		return "D";
	case 4:		return "E";
	case 5:		return "F";
	case 6:		return "G";
	case 7:		return "H";
	case 8:		return "I";
	}
	return "error";
}

int main()
{

    // 그래프를 인접 행렬(adjacency matrix)로 표현
	//   A B C D E F G H J
	// A 0 6 3 2 X X X X X
	// B X 0 X X 2 X X X X
	// C X 2 0 X X 4 X X X
	// D X X X 0 X X 1 X X 
	// E X X X X 0 X X 1 X
	// F X X X X X 0 X X 3
	// G X X X X X 3 0 X X 
	// H X X X X X X X 0 X
	// I X X X X X X X 1 0
	int Matrix[NUM_OF_NODES][NUM_OF_NODES] = {
		{0, 6, 3, 2, X, X, X, X, X},
		{X, 0, X, X, 2, X, X, X, X},
		{X, 2, 0, X, X, 4, X, X, X},
		{X, X, X, 0, X, X, 1, X ,X},
		{X, X, X, X, 0, X, X, 1, X},
		{X, X, X, X, X, 0, X, X, 3},
		{X, X, X, X, X, 3, 0, X, X},
		{X, X, X, X, X, X, X, 0, X},
		{X, X, X, X, X, X, X, 1, 0}
	};


	int Distance[NUM_OF_NODES];
	int PreNode[NUM_OF_NODES];
	int nStartPos = 0;
	int nEndPos = 7;
	Dijkstra(NUM_OF_NODES, Matrix, nStartPos, Distance, PreNode);
	int a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, i=0;
	a = Distance[0];
	b = Distance[1];
	c = Distance[2];
	d = Distance[3];
	e = Distance[4];
	f = Distance[5];
	g = Distance[6];
	h = Distance[7];
	i = Distance[8];
	printf("A(start) ===> H(end)\n");
	printf("                                                                \n");
    printf("|--------- 6 ----> B(%d) ----- 2 -----> E(%d) ---- 1 ---> H(%d) \n", b, e, h);
	printf("|                  ^                                      ^     \n");
    printf("|                  |                                      |     \n");
    printf("|                  2                                      1     \n");
    printf("|                  |                                      |     \n");
	printf("A(%d) ---- 3 ----> C(%d) ----- 4 -----> F(%d) ---- 3 ---> I(%d) \n", a, c, f, i);
    printf("|                                       ^                       \n");
	printf("|                                       |                       \n");
	printf("|                                       3                       \n");
	printf("|                                       |                       \n");
	printf("|--------- 2 ----> D(%d) ----- 1 -----> G(%d)                   \n", d, g);
	printf("                                                                \n");
	printf("                                                                \n");


	// 최단 경로 파악
	std::stack<int> ShortestPath;
	int temp = nEndPos;
	for (int i=0; i<NUM_OF_NODES; i++)
	{
		ShortestPath.push(temp);
		if (temp == 0)
		{
			break;
		}
		temp = PreNode[temp];
	}
	// 최단 경로 출력
	while (ShortestPath.empty() == false)
	{
		printf("%s", GetNodeName(ShortestPath.top()) );
		ShortestPath.pop();
		if (ShortestPath.empty() == false)
		{
			printf(" -> ");
		}
	}
	printf("\n");
	return 0;
}

