/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 23:01:08
 * Url: https://codeforces.com/contest/1405/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int T, N, K;
string S;
set<char> V[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> K >> S;
		S = " " + S;
		for (int i = 1; i <= K; ++i) {
			V[i].clear();
			for (int j = i; j <= N; j += K) V[i].insert(S[j]);
		}
		bool flag = 1;
		int cnt = 0;
		for (int i = 1; i <= K; ++i) {
			if (V[i].find('0') != V[i].end() && V[i].find('1') != V[i].end()) {
				flag = 0;
				break;
			}
			if (V[i].find('0') != V[i].end()) {
				for (int j = i; j <= N; j += K) S[j] = '0';
				++cnt;
			} else if (V[i].find('1') != V[i].end()) {
				for (int j = i; j <= N; j += K) S[j] = '1';
			}
		}
		int A[2] = {0, 0};
		for (int i = 1; i <= K; ++i) {
			if (S[i] == '?') {
				if (cnt < K / 2) {
					for (int j = i; j <= N; j += K) S[j] = '0';
					++cnt;
				} else {
					for (int j = i; j <= N; j += K) S[j] = '1';
				}
			}
		}
		for (int i = 1; i <= K; ++i) A[S[i] - '0']++;
		if (A[0] != A[1]) flag = 0;
		for (int i = K + 1; i <= N; ++i) {
			A[S[i - K] - '0']--;
			A[S[i] - '0']++;
			if (A[0] != A[1]) {
				flag = 0;
				break;
			}
		} 
		if (!flag) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}
