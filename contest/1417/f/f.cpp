/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-28 20:42:31
 * Url: https://codeforces.com/contest/1417/problem/F
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;

int N, M, Q;
int A[MAXN], Anc[MAXN], Del[MAXN], Rt[MAXN];
pair<int, int> E[MAXN], B[MAXN];
vector<int> G[MAXN];

int findAnc(int x) {
	return x == Anc[x] ? x : Anc[x] = findAnc(Anc[x]);
}

void merge(int x, int y) {
	x = findAnc(x), y = findAnc(y);
	if (x == y) return ;
	Anc[x] = Anc[y] = ++N;
	Anc[N] = N;
	G[N].push_back(x);
	G[N].push_back(y);
}

int Sz[MAXN], Dfn[MAXN], Id[MAXN], cntD;

int dfs(int x) {
	Dfn[++cntD] = x;
	Id[x] = cntD;
	Sz[x] = 1;
	for (auto u : G[x]) Sz[x] += dfs(u);
	return Sz[x];
}

int Mx[MAXN << 2];

int mx(int x, int y) {
	return A[x] > A[y] ? x : y;
}

void pushUp(int rt) {
	Mx[rt] = mx(Mx[rt << 1], Mx[rt << 1 | 1]);
}

void build(int rt, int l, int r) {
	if (l == r) {
		Mx[rt] = Dfn[l];
		return ;
	}
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	pushUp(rt);
}

int query(int rt, int l, int r, int a, int b) {
	if (a <= l && r <= b) return Mx[rt];
	int m = (l + r) >> 1, res = 0;
	if (a <= m) res = mx(res, query(rt << 1, l, m, a, b));
	if (m < b) res = mx(res, query(rt << 1 | 1, m + 1, r, a, b));
	return res;
}

void update(int rt, int l, int r, int p, int x) {
	if (l == r) {
		A[Mx[rt]] = x;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) update(rt << 1, l, m, p, x);
	else update(rt << 1 | 1, m + 1, r, p, x);
	pushUp(rt);
}

int main() {
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
	for (int i = 1; i <= M; ++i) scanf("%d%d", &E[i].first, &E[i].second);
	for (int i = 1; i <= N; ++i) Anc[i] = i;
	for (int i = 1; i <= Q; ++i) {
		scanf("%d%d", &B[i].first, &B[i].second);
		if (B[i].first == 2) Del[B[i].second] = 1;
	}
	for (int i = 1; i <= M; ++i) {
		if (!Del[i]) merge(E[i].first, E[i].second);
	}
	for (int i = Q; i >= 1; --i) {
		if (B[i].first == 2) {
			merge(E[B[i].second].first, E[B[i].second].second);
		} else {
			Rt[i] = findAnc(B[i].second);
		}
	}
	for (int i = 1; i <= N; ++i) {
		if (i == findAnc(i)) Sz[i] = dfs(i);
	}
	build(1, 1, N);
	for (int i = 1; i <= Q; ++i) {
		if (B[i].first == 1) {
			int p = query(1, 1, N, Id[Rt[i]], Id[Rt[i]] + Sz[Rt[i]] - 1);
			printf("%d\n", A[p]);
			update(1, 1, N, Id[p], 0);
		}
	}
	return 0;
}
