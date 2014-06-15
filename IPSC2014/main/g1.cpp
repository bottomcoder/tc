#include <cstdio>
#include <cstring>

int dp[1 << 20][101];
int n;
char table[101];
int sushi[20], sn;

int getAns(int stat, int turn)
{
	int &ret = dp[stat][turn];
	if(ret != -1) return ret;

	ret = 0;
	for(int i = 0; i < sn; i++)
	{
		if((stat & (1 << i)) == 0) continue;
		int loc = sushi[i] - turn;
		if(loc < 0) continue;

		if(getAns(stat ^ (1 << i), turn + 1) == 0) ret = 1;
	}

	return ret;
}

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d %s", &n, table);
		sn = 0;
		for(int i = 0; i < n; i++) if(table[i] == '1') sushi[sn++] = i;

		memset(dp, -1, sizeof(dp));
		if(getAns((1 << sn) - 1, 0) == 1) printf("Adam\n");
		else printf("Betka\n");
	}

	return 0;
}	
