/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-09 14:50:39
 * Url: https://codeforces.com/contest/1407/problem/E
**/
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 500000 + 5;
const int INF = 0x3f3f3f3f;
 
int N, M;
vector<int> G[MAXN][2];
int Dis[MAXN][2];
bool Inq[MAXN];
queue<int> Que;
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	for (int i = 1, u, v, w; i <= M; ++i) {
		cin >> u >> v >> w;
		G[v][w].emplace_back(u);
	}
	memset(Dis, 0x3f, sizeof Dis);
	Dis[N][0] = Dis[N][1] = 0;
	Que.push(N);
	while (!Que.empty()) {
		int x = Que.front(); Que.pop();
		Inq[x] = 0;
		int d = max(Dis[x][0], Dis[x][1]) + 1;
		for (int i = 0; i < 2; ++i) {
			for (auto u : G[x][i]) {
				if (Dis[u][i] <= d) continue;
				Dis[u][i] = d;
				if (!Inq[u]) {
					Que.push(u);
					Inq[u] = 1;
				}
			}
		}
	}
	int ans = max(Dis[1][0], Dis[1][1]);
	if (ans == INF) ans = -1;
	cout << ans << endl;
	for (int i = 1; i <= N; ++i) cout << (Dis[i][0] < Dis[i][1]);
	return 0;
}
