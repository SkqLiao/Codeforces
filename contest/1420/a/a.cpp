/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-24 22:35:18
 * Url: https://codeforces.com/contest/1420/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e4 + 5;

struct BinaryIndexedTree {
	int A[MAXN], n;
	void init(int n) {
		this->n = n;
		memset(A, 0, sizeof(int) * (n + 1));
	}
	int lowbit(int x) {
		return x & -x;
	}
	void add(int p, int x) {
		for (; p <= n; p += lowbit(p)) {
			A[p] += x;
		}
	}
	int query(int p) {
		int res = 0;
		for (; p > 0; p -= lowbit(p)) {
			res += A[p];
		}
		return res;
	}
} bit;
std::pair<int, int> F[MAXN];

int T, N;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &F[i].first);
			F[i].second = i;
		}
		std::sort(F + 1, F + N + 1, std::greater<std::pair<int, int> >());
		bit.init(N);
		long long ans = 0;
		for (int i = 1; i <= N; ++i) {
			bit.add(F[i].second, 1);
			ans += bit.query(F[i].second - 1);
		}
		puts(ans <= 1ll * N * (N - 1) / 2 - 1 ? "YES" : "NO");
	}
	return 0;
}
