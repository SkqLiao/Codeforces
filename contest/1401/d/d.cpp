/* Code Information
 * Author: Skqliao
 * Time: 2020-08-25 00:30:29
 * Url: https://codeforces.com/contest/1401/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

int T;
int N, M;
long long A[MAXN], B[MAXN];
vector<int> E[MAXN];
int id;

int dfs(int x, int fa) {
	int sz = 1;
	for (auto u : E[x]) {
		if (u != fa) sz += dfs(u, x);
	}
	A[id++] = 1ll * sz * (N - sz);
	return sz;
}

void solve() {
	scanf("%d", &N);
	id = 0;
	for (int i = 1; i <= N; ++i) E[i].clear();
	for (int i = 1, u, v; i < N; ++i) {
		scanf("%d%d", &u, &v);
		E[u].push_back(v);
		E[v].push_back(u);
	}
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) scanf("%lld", &B[i]);
	dfs(1, 0);
	sort(A, A + N - 1, greater<long long>());
	sort(B, B + M, greater<long long>());
	long long ans = 0;
	if (M < N - 1) {
		for (int i = 0; i < M; ++i) ans = (ans + A[i] * B[i]) % MOD;
		for (int i = M; i < N - 1; ++i) ans = (ans + A[i]) % MOD;
	} else {
		for (int i = 0; i <= M - N; ++i) B[M - N + 1] = B[M - N + 1] * B[i] % MOD;
		for (int i = M - N + 1; i < M; ++i) ans = (ans + A[i - M + N - 1] * B[i]) % MOD;
	}
	printf("%lld\n", ans);
}

int main() {
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
