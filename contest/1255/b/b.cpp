/* Code Information
 * Author: Skqliao
 * Time: 2020-07-31 10:15:47
 * Url: https://codeforces.com/contest/1255/problem/B
**/

#include <bits/stdc++.h>

const int MAXN = 1000 + 5;

int T, N, M;
int A[MAXN];

void solve() {
	int sum = 0;
	for (int i = 1; i <= N; ++i) sum += 2 * A[i];
	printf("%d\n", sum);
	for (int i = 1; i < N; ++i) printf("%d %d\n", i, i + 1);
	printf("%d %d\n", N, 1);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		if (M < N || N == 2) puts("-1");
		else solve();
	}
	return 0;
}
