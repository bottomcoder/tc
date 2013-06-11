#include <cstdio>
#include <cstring>

long long dp[1000001];

long long getAns(long long cur)
{
	long long &ret = dp[cur];
	if(ret != -1) return ret;

	ret = 0;
	if(cur > 1)
	{
		if(cur % 3 == 0) ret = (cur / 3) * (cur / 3 * 2) + getAns(cur / 3) + getAns(cur / 3 * 2);
		else if (cur % 2 == 0) ret = (cur / 2) * (cur / 2) + 2 * getAns(cur / 2);
		else ret = cur - 1 + getAns(cur - 1);
	}

	return ret;
}

int main(void)
{
	memset(dp, -1, sizeof(dp));

	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld\n", getAns(n));
	}

	return 0;
}
