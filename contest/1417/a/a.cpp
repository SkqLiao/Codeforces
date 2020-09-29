/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-27 23:05:40
 * Url: https://codeforces.com/contest/1417/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000 + 5;

int T, N, K, A[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &K);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		int mn = 1;
		for (int i = 1; i <= N; ++i) if (A[i] < A[mn]) mn = i;
		int ans = 0;
		for (int i = 1; i <= N; ++i) {
			if (i == mn) continue;
			ans += (K - A[i]) / A[mn];
		}
		printf("%d\n", ans);
	}
	return 0;
}
