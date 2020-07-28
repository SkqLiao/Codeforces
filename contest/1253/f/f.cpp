/* Code Information
 * Author: Skqliao
 * Time: 2020-07-27 23:44:52
**/
#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;
const int MAXM = 3e5 + 5;

int N, M, K, Q;

struct Graph {
	struct Edge {
		int u, v;
		long long w;
		int nxt;
		bool operator < (const Edge &x) const {
			return w < x.w;
		}
	} E[MAXM << 1];
	int H[MAXN], cntE;
	void addEdge(int u, int v, long long w) {
		E[++cntE] = (Edge) {u, v, w, H[u]};
		H[u] = cntE;
	}
} G, T;

std::priority_queue<std::pair<int, long long>> Pq;
long long Dis[MAXN];

void Dijkstra() {
    memset(Dis, 0x3f, sizeof Dis);
    for (int i = 1; i <= K; ++i) {
		Pq.push(std::make_pair(0, i));
		Dis[i] = 0;
	}
    while (!Pq.empty()) {
        while (!Pq.empty() && -Pq.top().first > Dis[Pq.top().second]) {
            Pq.pop();
        }
        if (Pq.empty()) {
            break;
        }
        int u = Pq.top().second; Pq.pop();
        for (int i = G.H[u]; i; i = G.E[i].nxt) {
			int v = G.E[i].v;
			if (Dis[v] > Dis[u] + G.E[i].w) {
				Dis[v] = Dis[u] + G.E[i].w;
				Pq.push(std::make_pair(-Dis[v], v));
			}
		}
    }
}

int Fa[MAXN];

int findFa(int x) {
	return Fa[x] == x ? x : Fa[x] = findFa(Fa[x]);
}

void Kruskal() {
	for (int i = 1; i <= G.cntE; ++i)
		G.E[i].w += Dis[G.E[i].u] + Dis[G.E[i].v];
	std::sort(G.E + 1, G.E + G.cntE + 1);
	for (int i = 1; i <= N; ++i) Fa[i] = i;
	for (int i = 1; i <= G.cntE; ++i) {
		int u = G.E[i].u, v = G.E[i].v;
		if (findFa(u) != findFa(v)) {
			Fa[findFa(v)] = findFa(u);
			T.addEdge(u, v, G.E[i].w);
			T.addEdge(v, u, G.E[i].w);
		}
	}
}

int Depth[MAXN];
long long Mx[MAXN][20];
int Anc[MAXN][20];

void dfs(int x, int fa) {
	Anc[x][0] = fa;
	Depth[x] = Depth[fa] + 1;
	for (int i = 1; (1 << i) <= Depth[x]; ++i) {
		Anc[x][i] = Anc[Anc[x][i - 1]][i - 1];
		Mx[x][i] = std::max(Mx[x][i - 1], Mx[Anc[x][i - 1]][i - 1]);
	}
	for (int i = T.H[x]; i; i = T.E[i].nxt) {
		int v = T.E[i].v;
		if (fa != v) {
			Mx[v][0] = T.E[i].w;
			dfs(v, x);
		}
	}
}

long long lca(int u, int v) {
	long long ans = 0;
	if (Depth[u] > Depth[v]) std::swap(u, v);
	for (int i = 0; (1 << i) <= Depth[v]; ++i) {
		if ((Depth[u] - Depth[v]) >> i & 1) {
			ans = std::max(ans, Mx[v][i]);
			v = Anc[v][i];
		}
	}
	if (u == v) return ans;
	for (int i = 19; i >= 0; --i) {
		if (Anc[u][i] != Anc[v][i]) {
			ans = std::max(ans, std::max(Mx[u][i], Mx[v][i]));
			u = Anc[u][i], v = Anc[v][i];
		}
	}
	return std::max(ans, std::max(Mx[u][0], Mx[v][0]));
}

int main() {
	scanf("%d%d%d%d", &N, &M, &K, &Q);
	for (int i = 1, u, v, w; i <= M; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		G.addEdge(u, v, w);
		G.addEdge(v, u, w);
	}
	Dijkstra();
	Kruskal();
	dfs(1, 0);
	for (int i = 1, u, v; i <= Q; ++i) {
		scanf("%d%d", &u, &v);
		printf("%lld\n", lca(u, v));
	}
	return 0;
}
