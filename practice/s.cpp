#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int main(void)
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int n;
		scanf("%d", &n);

		char str[501];
		gets(str);

		int ans = 0;
		double loudness = 0;

		for(int i = 0; i < n; i++)
		{
			gets(str);
			int len = strlen(str);

			bool asterisk = false;
			double cnt = 0, sum = 0;

			for(int j = 0; j < len; j++)
			{
				if(isspace(str[j])) continue;
				if(str[j] == '*') { asterisk = !asterisk; continue; }
				if(isalpha(str[j]) == false) continue;

				bool allUpper = true;

				while(j < len && isalpha(str[j]))
				{
					if(islower(str[j])) allUpper = false;
					j++;
				}
				j--;

				cnt++;
				double cur = 1;
				if(asterisk) cur *= 3;
				if(allUpper) cur *= 2;

				sum += cur;
			}

			if(abs(loudness - sum / cnt) > 1e-9 && loudness < sum / cnt)
			{
				loudness = sum / cnt;
				ans = i + 1;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
