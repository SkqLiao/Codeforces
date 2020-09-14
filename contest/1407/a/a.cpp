/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 22:35:33
 * Url: https://codeforces.com/contest/1407/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int T, N, A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		int cnt = 0;
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = 1; i <= N; ++i) if (A[i] == 1) ++cnt;
		if (cnt > N / 2) {
			if (cnt % 2) --cnt;
			cout << cnt << endl;
			for (int i = 1; i <= cnt; ++i) cout << 1 << " ";
		} else {
			cout << N - cnt << endl;
			for (int i = 1; i <= N - cnt; ++i) cout << 0 << " ";
		}
		cout << endl;
	}
	return 0;
}
