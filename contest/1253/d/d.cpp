/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 20:23:39
**/

#include <bits/stdc++.h>

const int MAXN = 200000 + 5;

int N, M;
std::vector<int> E[MAXN];

void addEdge(int u, int v) {
	E[u].push_back(v);
	E[v].push_back(u);
}

int ans;
int Fa[MAXN];
bool Vis[MAXN];
int Mx[MAXN];

int findFa(int x) {
	return Fa[x] == x ? x : findFa(Fa[x]);
}

void Union(int x, int y) {
	++ans;
	y = findFa(y);
	x = findFa(x);
	Fa[y] = x;
	Mx[x] = std::max(Mx[x], Mx[y]);
}

void bfs(int x) {
	Mx[x] = x;
	Fa[x] = x;
	Vis[x] = 1;
	static std::queue<int> Que;
	Que.push(x);
	while (!Que.empty()) {
		int u = Que.front();
		Que.pop();
		for (auto v : E[u]) {
			if (!Vis[v]) {
				Vis[v] = 1;
				Fa[v] = x;
				Mx[x] = std::max(Mx[x], v);
				Que.push(v);
			}
		}
	}
}

void Solve(int x) {
	for (int i = x; i < Mx[x]; ++i)
		if (findFa(i) != x) Union(x, i);
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0, u, v; i < M; ++i) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 1; i <= N; ++i)
		if (!Vis[i]) bfs(i);
	for (int i = 1; i <= N; ++i)
		if (findFa(i) == i) Solve(i);
	printf("%d\n", ans);
	return 0;
}
