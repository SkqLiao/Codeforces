/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 22:00:29
 * Url: https://codeforces.com/contest/1406/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N;
vector<int> G[MAXN], res;
int Sz[MAXN];

void dfs(int x, int fa) {
	Sz[x] = 1;
	bool flag = 1;
	for (auto u : G[x]) {
		if (u != fa) {
			dfs(u, x);
			Sz[x] += Sz[u];
			flag &= (Sz[u] <= N / 2);
		}
	}
	flag &= (N - Sz[x] <= N / 2);
	if (flag) res.push_back(x);
}

int node1, node2;

void dfs2(int x, int fa) {
	if (G[x].size() == 1) node1 = x, node2 = fa;
	for (auto u : G[x]) {
		if (u != fa) dfs2(u, x);
	}
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		if (N & 1) {
			int u, v;
			for (int i = 1; i < N; ++i) cin >> u >> v;
			cout << u << " " << v << endl;
			cout << u << " " << v << endl;
			continue;
		}
		for (int i = 1; i <= N; ++i) G[i].clear();
		res.clear();
		for (int i = 1, u, v; i < N; ++i) {
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1, 0);
		if (res.size() == 1) {
			cout << 1 << " " << G[1].front() << endl;
			cout << 1 << " " << G[1].front() << endl;
		} else {
			dfs2(res.front(), res.back());
			cout << node1 << " " << node2 << endl;
			cout << res.back() << " " << node1 << endl;
		}
	}
	return 0;
}
