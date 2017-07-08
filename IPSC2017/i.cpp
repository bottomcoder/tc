#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[500000], reve[500000];

int _index[500000], low[500000];
int curind;

vector<int> scc[500000];
int sn;

bool inStack[500000];
stack<int> st;

int shash[500000];
int sStart, sEnd;

bool isSelf[500000];

void tarjan(int u) {
	_index[u] = low[u] = curind++;
	inStack[u] = true;
	st.push(u);

	for(auto v: edges[u]) {
		if(_index[v] == -1) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(inStack[v]) low[u] = min(low[u], _index[v]);
	}

	if(low[u] == _index[u]) {
		while(true) {
			int cur = st.top();
			st.pop();
			inStack[cur] = false;
			scc[sn].push_back(cur);
			shash[cur] = sn;
			if(cur == 0) sStart = sn;
			if(cur == n - 1) sEnd = sn;
			if(cur == u) break;
		}
		sn++;
	}
}

bool isPossible[500000];

long long dpGoal[500000], dpStart[500000];
const long long MOD = 1000000009;
vector<int> se[500000], rse[500000];

void findPossible(int u) {
	isPossible[u] = true;
	for(auto v: reve[u])
		if(!isPossible[v]) 
			findPossible(v);
}

long long findWays(int u, int goal, vector<int> edges[], long long table[]) {
	long long &ret = table[u];
	if(ret != -1) return ret;

	ret = 0;
	if(u == goal) ret = 1;
	else {
		for(auto v: edges[u])
			ret = (ret + findWays(v, goal, edges, table)) % MOD;
	}

	return ret;
}

bool isVisited[500000];
vector<int> ans;
void findAns(int u) {
	if(!isPossible[u]) return;
	isVisited[u] = true;
	for(auto v: edges[u])
		if(!isVisited[v])
			findAns(v);

	int si = shash[u];
	if(scc[si].size() == 1 and !isSelf[u]) {
		long long bef = findWays(shash[u], sStart, rse, dpStart);
		long long aft = findWays(shash[u], sEnd, se, dpGoal);
		long long tot = bef * aft % MOD;
		if(tot == findWays(shash[0], sEnd, se, dpGoal)) ans.push_back(u);
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		sn = 0;
		for(int i = 0;i <n ; i++) {
			edges[i].clear();
			reve[i].clear();
			scc[i].clear();
			se[i].clear();
			rse[i].clear();
		}

		fill(isSelf, isSelf + n, false);

		for(int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(u != v) {
				edges[u - 1].push_back(v - 1);
				reve[v - 1].push_back(u - 1);
			} else isSelf[u - 1] = true;
		}

		for(int i =0 ; i < n; i++) {
			sort(edges[i].begin(), edges[i].end());
			sort(reve[i].begin(), reve[i].end());
			edges[i].erase(unique(edges[i].begin(), edges[i].end()), edges[i].end());
			reve[i].erase(unique(reve[i].begin(), reve[i].end()), reve[i].end());
		}
		
		fill(_index, _index + n, -1);
		fill(inStack, inStack + n, false);
		curind = 0;
		while(!st.empty()) st.pop();
		for(int i = 0; i < n; i++)
			if(_index[i] == -1)
				tarjan(i);

		for(int i = 0; i < sn; i++) {
			for(int u: scc[i])
				for(int v: edges[u])
					se[i].push_back(shash[v]);
			sort(se[i].begin(), se[i].end());
			se[i].erase(unique(se[i].begin(), se[i].end()), se[i].end());
			for(auto j: se[i]) rse[j].push_back(i);
		}

		fill(isPossible, isPossible + n, false);
		findPossible(n - 1);

		ans.clear();
		fill(isVisited, isVisited + n, false);
		fill(dpGoal, dpGoal + n, -1);
		fill(dpStart, dpStart + n, -1);
		findAns(0);
/*
		for(int i =0 ; i < sn ; i++) {
			printf("\t%d:", i);
			for(int u: scc[i]) printf(" %d", u + 1);
			printf("\n");
		}
		*/
		reverse(ans.begin(), ans.end());
		printf("%d\n", (int)ans.size());
		for(int i = 0; i < ans.size(); i++) {
			if(i > 0) printf(" ");
			printf("%d", ans[i] + 1);
		}
		printf("\n");
	}

	return 0;
}
