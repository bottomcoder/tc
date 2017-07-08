#include <string>
#include <iostream>
#include <random>

using namespace std;

vector<int> arr;
string ans;

int main(void) {
	for(int lv = 0; lv < 2; lv++) {
		string s;
		cin >> s;

		arr.clear();
		for(char ch: s) {
			ch -= 33;
			int base = 27;
			for(int i = 0; i < 4; i++) {
				arr.push_back((int)(ch / base));
				ch %= base;
				base /= 3;
			}
		}

		int cnt[2][2] = {{0, 0}, {0, 0}};
		for(int i = 1; i < arr.size(); i++) {
			if(arr[i - 1] == 2 or arr[i] == 2) continue;
			cnt[arr[i - 1]][arr[i]]++;
		}

		auto zeroRand = std::bind(std::uniform_int_distribution<int>(1, cnt[0][0] + cnt[0][1]), mt19937(time(nullptr)));
		auto oneRand = std::bind(std::uniform_int_distribution<int>(1, cnt[1][0] + cnt[1][1]), mt19937(time(nullptr)));

		ans = "";
		for(int i = 0; i < arr.size(); i++) {
//			cout << i << " " << arr.size() << "\n";
			if(arr[i] == 2) {
				if(i == 0) {
					arr[i] = 0;
					ans += "0";
					continue;
				}

				if(arr[i - 1] == 0) {
					auto v = zeroRand();
//					cout << "\t a randDone " << v << " " << cnt[0][0] << " " << cnt[0][1] << "\n";
					if(v <= cnt[0][0]) {
						arr[i] = 0;
						ans += "0";
					} else {
//						cout << "aaaa\n";
						arr[i] = 1;
						ans += "1";
					}
//					cout << "woowwa done\n";
				} else {
					auto v = oneRand();
//					cout << "\t b randDone\n";
					if(v <= cnt[1][0]) {
						arr[i] = 0;
						ans += "0";
					} else {
						arr[i] = 1;
						ans += "1";
					}
				}
			}
		}

		cout << ans << "\n";
	}

	return 0;
}

	
