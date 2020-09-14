/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 23:29:52
 * Url: https://codeforces.com/contest/1405/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N, Sa, Sb, Da, Db;
vector<int> G[MAXN];
int D[MAXN], mx;

void dfs(int x, int fa) {
	if (D[mx] < D[x]) mx = x;
	for (auto u : G[x]) {
		if (u == fa) continue;
		D[u] = D[x] + 1;
		dfs(u, x);
	}
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> Sa >> Sb >> Da >> Db;
		for (int i = 1; i <= N; ++i) G[i].clear();
		for (int i = 1, a, b; i < N; ++i) {
			cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		memset(D, 0, sizeof D);
		dfs(Sa, 0);
		int dis = D[Sb];
		D[mx] = 0;
		dfs(mx, 0);
		if (dis <= Da || 2 * Da >= Db || D[mx] <= 2 * Da) cout << "Alice" << endl;
		else cout << "Bob" << endl;
	}
	return 0;
}
