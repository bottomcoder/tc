#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector <long long> coord;
bool isMiddle[3000000];
long long data[1000000][2];
int counter[3000000][2];

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		long long l, K;
		int n;
		scanf("%lld %d %lld", &l, &n, &K);

		coord.clear();
		coord.push_back(1);
		coord.push_back(l + 1);
		
		for(int i = 0; i < n; i++)
		{
			long long from, to;
			scanf("%lld %lld", &from, &to);
			data[i][0] = from, data[i][1] = to;

			coord.push_back(from);
			coord.push_back(to + 1);
			if(from + K <= to) coord.push_back(from + K);
			if(to - K >= from) coord.push_back(to - K + 1);
		}

		sort(coord.begin(), coord.end());
		coord.erase(unique(coord.begin(), coord.end()), coord.end());

		fill(isMiddle, isMiddle + coord.size(), false);
		fill(&counter[0][0], &counter[coord.size()][0], 0);

		for(int i = 0; i < n; i++)
		{
			long long s = data[i][0], e = data[i][1];
			int start = lower_bound(coord.begin(), coord.end(), s) - coord.begin();

			for(int j = start; e + 1 != coord[j]; j++)
			{
				long long cur = coord[j];
				if(cur >= s + K) counter[j][0]++;
				if(cur <= e - K) counter[j][1]++;
				if(s + K <= cur && cur <= e - K) isMiddle[j] = true;
			}
		}

		long long ans = 0;
		for(int i = 0; i < coord.size() - 1; i++)
		{
			if(isMiddle[i] == false)
			{
				if(counter[i][0] == 0 || counter[i][1] == 0) ans += coord[i + 1] - coord[i];
			}
			else
			{
				if(counter[i][0] == 1 && counter[i][1] == 1) ans += coord[i + 1] - coord[i];
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}
