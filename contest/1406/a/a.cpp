/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 21:45:44
 * Url: https://codeforces.com/contest/1406/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;

int T, N, A[MAXN];
int Cnt[MAXN];

int main() {
	cin >> T;
	while (T--) {
		int ans = 0, mx = 0;
		cin >> N;
		memset(Cnt, 0, sizeof Cnt);
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = 1; i <= N; ++i) ++Cnt[A[i]];
		for (int i = 1; i <= N; ++i) mx = max(mx, A[i]);
		for (int i = 0; i <= mx + 1; ++i) {
			if (!Cnt[i]) {
				ans = i;
				break;
			}
			--Cnt[i];
		}
		for (int i = 0; i <= mx + 1; ++i) {
			if (!Cnt[i]) {
				ans += i;
				break;
			}
			--Cnt[i];
		}
		cout << ans << endl;
	}
	return 0;
}
