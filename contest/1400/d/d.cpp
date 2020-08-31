/* Code Information
 * Author: Skqliao
 * Time: 2020-08-26 23:49:14
 * Url: https://codeforces.com/contest/1400/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3000 + 5;

int T, N, A[MAXN];
int CntL[MAXN][MAXN], CntR[MAXN][MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		memset(CntL, 0, sizeof CntL);
		memset(CntR, 0, sizeof CntR);
		for (int i = 1; i <= N; ++i) {
			memcpy(CntL[i], CntL[i - 1], MAXN * sizeof(int));
			CntL[i][A[i]]++;
		}
		for (int i = N; i >= 1; --i) {
			memcpy(CntR[i], CntR[i + 1], MAXN * sizeof(int));
			CntR[i][A[i]]++;
		}
		long long ans = 0;
		for (int i = 1; i <= N; ++i) {
			for (int j = i + 1; j <= N; ++j) {
				ans += CntL[i - 1][A[j]] * CntR[j + 1][A[i]];
			}
		}
		cout << ans << endl;
	}
	return 0;
}
