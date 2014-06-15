#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	while(T--)
	{
		string p, q;
		cin >> p >> q;
		int maxLength = 0;
		for(int i = 0; i < p.size() && i < q.size(); i++)
		{
			if(p[i] != q[i]) break;
			maxLength++;
		}

		int cand1 = (q.size() - maxLength) + p.size() - maxLength + 1;
		int cand2 = 1 + p.size() + 1;

		if(cand1 < cand2)
		{
			for(int i = 0; i < q.size() - maxLength; i++) cout << "<";
			cout << p.substr(maxLength) << "*" << endl;
		}
		else { cout << "*" << p << "*" << endl; }
	}

	return 0;
}
