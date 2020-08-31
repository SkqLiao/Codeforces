/* Code Information
 * Author: Skqliao
 * Time: 2020-08-30 22:35:47
 * Url: https://codeforces.com/contest/1397/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int T, N;
string S;
map<char, int> Cnt;

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		Cnt.clear();
		for (int i = 0; i < N; ++i) {
			cin >> S;
			for (auto u : S) ++Cnt[u];
		}
		bool flag = 1;
		for (auto p : Cnt) {
			if (p.second % N != 0) flag = 0;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
