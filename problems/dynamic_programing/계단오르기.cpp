/******************************************************************************
https://www.acmicpc.net/problem/2579

1. 계단은 한 번에 한 계단씩 또는 두 계단씩 오를 수 있다. 즉, 한 계단을 밟으면서 이어서 다음 계단이나, 다음 다음 계단으로 오를 수 있다.
2. 연속된 세 개의 계단을 모두 밟아서는 안 된다. 단, 시작점은 계단에 포함되지 않는다.
3. 마지막 도착 계단은 반드시 밟아야 한다.

memo[i][j] : i번째 칸에서 연속한 j개의 계단을 밟은 상태의 최대값

*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define MAX(x, y)((x) > (y) ? x : y)
#define MAX_STAIRS (300)
#define MAX_CONTINUE_STAIRS (2)
#include<cstdio>

int n_stairs;
int stairs[MAX_STAIRS];
int memo[MAX_STAIRS][MAX_CONTINUE_STAIRS + 1];

void init()
{
	scanf("%d", &n_stairs);
	for (int i = 0; i < n_stairs; i++)
		scanf("%d", &stairs[i]);
}


int solve()
{
    memo[0][1] = stairs[0];
    memo[1][2] = memo[0][1] + stairs[1];
    memo[1][1] = stairs[1];
    

	for (int i = 2; i < n_stairs; i++)
	{
		memo[i][1] = MAX(memo[i - 2][1], memo[i - 2][2]) + stairs[i];
		memo[i][2] = memo[i - 1][1] + stairs[i];
	}
	return MAX(memo[n_stairs - 1][1], memo[n_stairs - 1][2]);
}

int main(void)
{
	init();
	printf("%d", solve());

	return 0;
}
