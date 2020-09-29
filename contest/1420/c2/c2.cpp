/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-25 23:24:07
 * Url: https://codeforces.com/contest/1420/problem/C2
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int T, N, Q;
int A[MAXN];
struct Matrix {
	long long B[2][2];
	Matrix operator * (const Matrix &x) {
		Matrix ans;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				ans.B[i][j] = max(B[i][j], x.B[i][j]);
			}
		}
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k) {
					ans.B[i][j] = max(ans.B[i][j], B[i][k] + x.B[k][j]);
				}
			}
		}
		return ans;
	}
	long long get() {
		return max(max(B[0][0], B[0][1]), max(B[1][0], B[1][1]));
	}
} S[MAXN << 2];

void pushUp(int rt) {
	S[rt] = S[rt << 1] * S[rt << 1 | 1];
}

void update(int rt, int x) {
	S[rt].B[0][0] = S[rt].B[1][1] = 0;
	S[rt].B[0][1] = x;
	S[rt].B[1][0] = -x;
}

void build(int rt, int l, int r) {
	if (l == r) {
		update(rt, A[l]);
		return ;
	}
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	pushUp(rt);
}

void modify(int rt, int l, int r, int p) {
	if (l == r) {
		update(rt, A[l]);
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) modify(rt << 1, l, m, p);
	else modify(rt << 1 | 1, m + 1, r, p);
	pushUp(rt);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &Q);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		build(1, 1, N);
		printf("%lld\n", S[1].get());
		for (int i = 1, l, r; i <= Q; ++i) {
			scanf("%d%d", &l, &r);
			swap(A[l], A[r]);
			modify(1, 1, N, l);
			modify(1, 1, N, r);
			printf("%lld\n", S[1].get());
		}
	}
	return 0;
}
