#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int data[32][32];
pair<int, int> gap[32][32];

int main(void)
{
	/*
	scanf("%*d");
	for(int i=0;i<21;i++) for(int j=0;j<32;j++) for(int k=0;k<32;k++) scanf("%d", data[j] + k);

	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			for(int k=0;k<32;k++) gap[i][j].first += abs(data[k][j] - data[k][i]);
			gap[i][j].second = j;
		}
		sort(gap[i], gap[i] + 32);
	}

	for(int i=0;i<32;i++)
	{
		vector <int> order;
		order.push_back(i);
		bool isVisit[32];
		memset(isVisit, 0, sizeof(isVisit));
		isVisit[i] = true;
		for(int j=0;j<31;j++)
		{
			int last = order[order.size() - 1];
			for(int k=0;k<32;k++)
			{
				if(isVisit[gap[last][k].second]) continue;
				isVisit[gap[last][k].second] = true;
				order.push_back(gap[last][k].second);
				break;
			}
		}

		string name;
		for(int i=0;i<order.size();i++)
		{
			char temp[10];
			sprintf(temp, "%02d", order[i]);
			if(i) name += " ";
			name += temp;
		}

		name += ".pgm";

		FILE *fp = fopen(name.c_str(), "w");
		fprintf(fp, "P2\n32 32\n256\n");
		for(int i=0;i<32;i++) for(int j=0;j<32;j++) fprintf(fp, "%d\n", data[i][order[j]]);
		fclose(fp);
	}

	*/

	int order[32] = {15, 2, 25, 1, 23, 28, 19, 7, 16, 11, 17, 14, 12, 21, 10, 3, 27, 26, 20, 31, 22, 5, 9, 24, 8, 29, 18, 30, 6, 4, 13, 0};
	freopen("i1.in", "r", stdin);
	int t;
	scanf("%d", &t);
	for(int i=0;i<t;i++)
	{
		for(int j=0;j<32;j++) for(int k=0;k<32;k++) scanf("%d", data[j] + k);
		char name[20];
		sprintf(name, "pic%03d.pgm", i + 1);
		FILE *fp = fopen(name, "w");
		fprintf(fp, "P2\n32 32\n256\n");
		for(int j=0;j<32;j++) for(int k=0;k<32;k++) fprintf(fp, "%d\n", data[j][order[k]]);
		fclose(fp);
	}

	return 0;
}
