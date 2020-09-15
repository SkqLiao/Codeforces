/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-15 17:24:21
 * Url: https://codeforces.com/contest/1401/problem/F
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = (1 << 18) + 5;

int N, M;
long long Sum[MAXN << 2];
bool Rev[20];

void pushUp(int rt) {
	Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}

void build(int rt, int l, int r) {
	if (l == r) {
		scanf("%lld", &Sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	pushUp(rt);
}

void update(int rt, int l, int r, int p, int x, int dep) {
	if (l == r) {
		Sum[rt] = x;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) update((rt << 1) + Rev[dep], l, m, p, x, dep - 1);
	else update((rt << 1 | 1) - Rev[dep], m + 1, r, p, x, dep - 1);
	pushUp(rt);
}

long long query(int rt, int l, int r, int a, int b, int dep) {
	if (a <= l && r <= b) return Sum[rt];
	int m = (l + r) >> 1;
	long long sum = 0;
	if (a <= m) sum += query((rt << 1) + Rev[dep], l, m, a, b, dep - 1);
	if (m < b) sum += query((rt << 1 | 1) - Rev[dep], m + 1, r, a, b, dep - 1);
	return sum;
}

int main() {
	scanf("%d%d", &N, &M);
	build(1, 1, 1 << N);
	for (int t = 0, opt, x, k; t < M; ++t) {
		scanf("%d", &opt);
		if (opt == 1) {
			scanf("%d%d", &x, &k);
			update(1, 1, 1 << N, x, k, N);
		} else if (opt == 2) {
			scanf("%d", &k);
			for (int i = 0; i <= k; ++i) Rev[i] ^= 1;
		} else if (opt == 3) {
			scanf("%d", &k);
			Rev[k + 1] ^= 1;
		} else {
			scanf("%d%d", &k, &x);
			printf("%lld\n", query(1, 1, 1 << N, k, x, N));
		}
	}
	return 0;
}
