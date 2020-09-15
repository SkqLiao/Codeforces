/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-15 11:43:16
 * Url: https://codeforces.com/contest/1401/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
const int MAX = 1e6 + 1;

int N, M;
vector<int> In[MAXN], Out[MAXN], P[MAXN][2];
long long ans = 1;

int Num[MAXN << 2];

void add(int rt, int l, int r, int p, int x) {
	if (l == r) {
		Num[rt] += x;
		return ;
	}
	int m = (l + r) >> 1;
	if (p <= m) add(rt << 1, l, m, p, x);
	else add(rt << 1 | 1, m + 1, r, p, x);
	Num[rt] = Num[rt << 1] + Num[rt << 1 | 1];
}

int query(int rt, int l, int r, int a, int b) {
	if (a <= l && r <= b) return Num[rt];
	int m = (l + r) >> 1, sum = 0;
	if (a <= m) sum += query(rt << 1, l, m, a, b);
	if (m < b) sum += query(rt << 1 | 1, m + 1, r, a, b);
	return sum;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, a, b, c; i < N; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		++a, ++b, ++c;
		In[b].push_back(a);
		Out[c].push_back(a);
		if (b == 1 && c == MAX) ++ans;
	}
	for (int i = 0, a, b, c; i < M; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		++a, ++b, ++c;
		if (b == 1) P[a][0].push_back(c);
		else P[a][1].push_back(b);
		if (b == 1 && c == MAX) ++ans;
	}
	fprintf(stderr, "ans=%lld\n", ans);
	for (int i = 1; i <= MAX; ++i) {
		for (auto u : In[i]) add(1, 1, MAX, u, 1);
		for (auto u : P[i][0]) 	ans += query(1, 1, MAX, 1, u);
		for (auto u : P[i][1]) 	ans += query(1, 1, MAX, u, MAX);
		for (auto u: Out[i]) add(1, 1, MAX, u, -1);
	}
	printf("%lld\n", ans);
	return 0;
}