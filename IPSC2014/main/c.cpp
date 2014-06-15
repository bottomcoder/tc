#include <cstdio>
#include <cstring>

bool isVisited[100001];

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		memset(isVisited, 0, sizeof(isVisited));

		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
		{
			int v;
			scanf("%d", &v);
			if(isVisited[v] == 1) continue;
			isVisited[v] = 1;
			printf("%d ", v);
		}
		printf("\n");
	}

	return 0;
}

