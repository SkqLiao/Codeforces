# Codeforces Round #600 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1253)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/71489)

## A. [Single Push](https://codeforces.com/contest/1253/problem/A)

### 题意

$t$ 组数据。每组数据给定两个长为 $n$ 的数组 $A$ 和 $B$，可以选择 $A$ 的一个子序列 $A[l,r]$，将其中的每个数增加 $x(x > 0)$，该操作至多进行一次。判断 $A$ 能否转化成 $B$。

$t\leq 20,n\leq 100000$

### 题解

初始化 $C_i=A_i-B_i$，若 $C_i\not=0$ 且 $C_i\not = C_{i-1}$，说明这是一个需要操作的新子序列，判断这样的 $i$ 的个数是否小于 $2$ 个。如果出现 $C_i < 0$，则一定不行。

复杂度 $O(t\cdot n)$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-24 20:54:20
**/

#include <bits/stdc++.h>
 
const int MAXN = 1e5 + 5;
 
int T, N, A[MAXN];
 
bool solve() {
	int cnt = 0, tmp;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &tmp);
		A[i] -= tmp;
	}
	for (int i = 1; i <= N; ++i) {
		if (A[i] > 0) return false;
		if (A[i] != A[i - 1] && A[i]) ++cnt;
	}
	return cnt <= 1;
}
 
int main() {
	scanf("%d", &T);
	while (T--)
		puts(solve() ? "YES" : "NO");
	return 0;
}
```

## B. [Silly Mistake](https://codeforces.com/contest/1253/problem/B)

### 题意

给定一个序列 $A[1\cdots n]$，判断能否将其划分成若干区间，使每个区间 $A[l_i,r_i]$ ，

- 对于一个正数 $x$，将 $x$ 插入集合 $S$
- 对于一个负数 $x$，将 $-x$ 从 $S$ 中取出

要求每个正数至多被插入一次（在该区间内），且取出时存在于 $S$，最后 $S$ 为空。

如果存在满足条件的划分方法，输出每一段的长度，不存在输出`-1`。

$n\leq 10^5$

### 题解

贪心，每次 $S$ 为空时将其划分成一个新区间，如此可以尽最大可能保证每个正整数 $x$ 只被插入一次。

然后用`std::set`或者直接哈希表维护区间即可。

复杂度 $O(n)$ 或 $O(n\log{n})$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 09:59:19
**/

#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int N, A[MAXN];
std::set<int> S, T;
std::vector<int> v;

void Solve() {
	int total = 0, cnt = 0, lst = 0;
	for (int i = 1; i <= N; ++i) {
		if (A[i] > 0) {
			if (T.find(A[i]) != T.end()) {
				puts("-1");
				return ;
			}
			S.insert(A[i]);
			T.insert(A[i]);
			total += A[i];
		} else {
			A[i] = -A[i];
			if (S.find(A[i]) == S.end()) {
				puts("-1");
				return ;
			}
			S.erase(A[i]);
			total -= A[i];
			if (total == 0) {
				++cnt;
				v.push_back(i - lst);
				lst = i;
				T.clear();
			}
		}
	}
	if (total != 0) {
		puts("-1");
		return ;
	}
	printf("%d\n", cnt);
	for (auto i : v) 
		printf("%d ", i);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	Solve();
	return 0;
}
```

## C. [Sweets Eating](https://codeforces.com/contest/1253/problem/C)

### 题意

有 $n$ 颗糖果，其糖度值分别为 $A[1\cdots n]$，每天最多吃 $m$ 颗糖果，且每颗糖果只能被吃一次。

若在第 $i$ 天吃了糖果 $j$，则获得的甜度为 $i\times A_j$，吃多个糖获得的甜度叠加。

依次求出如果一共吃 $i(1\leq i\leq n)$ 颗糖果，获得的甜度最小值是多少。

$n\leq 200000$

### 题解

先考虑对于 $t$ 颗糖果，如何吃使得甜度最小。显然吃甜度最小的 $t$ 颗，且将甜度大的放在前面吃。

具体而言，设 $C$ 为 $A$ 从小到大的有序排列。则吃法如下： $(C_t,\cdots,C_{t-m+1}),(C_{t-m},\cdots,C_{t-2m+1}) \cdots (\cdots,C_1)$

当增加一颗糖果 $C_{t+1}$ 时，将 $C_{t+1}$ 放在最前面，然后其余的糖果依次往后挪是最优解。

可以意会出对于大部分糖果而言，增加一颗糖果后甜度不变，而位于每天尾端的糖果则会挪到下一天，甜度增加 $C_i$。

那么只要维护位于每天尾端糖果的甜度和 $s$，则可以快速计算出下一天的甜度 $T_i$，即 $T_i=T_{i-1}+C_i+s$。

现在考虑如何维护 $s$，不难想到它是 $m$ 个一循环，因为位于某一天尾端的糖果挪动 $m$ 次后又会到下一天的尾端，因而可以用一个数组 $s[0\cdots m-1]$ 来维护。

注意答案会超过`int`范围。

复杂度 $O(n\log{n})$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 11:30:12
**/

#include <bits/stdc++.h>

const int MAXN = 200000 + 5;

int N, M;
long long A[MAXN], B[MAXN];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
	std::sort(A + 1, A + N + 1);
	long long total = 0;
	for (int i = 1, cur = 0; i <= N; ++i, (cur += 1) %= M) {
		total += A[i] + B[cur];
		printf("%lld ", total);
		B[cur] += A[i];
	}
	return 0;
}
```

## D. [Harmonious Graph](https://codeforces.com/contest/1253/problem/D)

### 题意

给定 $n$ 个点 $m$ 条边的无向图，增加最少的边数，使得图满足：若点 $l,r(l < r)$ 连通，则 $l$ 与 $i(l < i < r)$ 都连通。

$n,m\leq 200000$

### 题解

先求出无向图的连通块，从小到大，对于 $i$ 所在的连通块，编号最小的点为 $i$（若有更小的点 $j$，则在 $j$ 时已经处理完该连通块，不会等到 $i$），最大的点 $b_i$。若 $i,j$ 不连通，将 $i$ 与 $j(i\ < j < b_i)$ 所在的连通块相连，并维护连通块的最大点编号 $b_i$。连通性用并查集维护。

复杂度 $O(n\alpha(n))$。

### 参考代码

```cpp
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
	return Fa[x] == x ? x : Fa[x] = findFa(Fa[x]);
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
```

## E. [Antenna Coverage](https://codeforces.com/contest/1253/problem/E)

### 题意

在数轴 $[1,m]$ 上，有 $n$ 盏灯，坐标依次为 $p_i$，范围为 $s_i$，即它可照亮 $[p_i-s_i,p_i+s_i]$ 。增加任意一盏灯的范围 $s_i\rightarrow s_i+1$ 花费为 $1$。求将 $[1,m]$ 全部照亮的最小花费（可以照亮 $[1,m]$ 以外的地方）。

$n\leq 80, m\leq 100000$

### 题解

设 $f_{i,j}$ 为前 $i$ 盏灯照亮 $[1,j]$ 的最小花费，初始化 $f_{0,0}=0$

$f_{i,j}=min\{f_{i-1,k}\}(k \geq j)$，显然覆盖 $[1,k]$包含了覆盖 $[1,j]$ 的情况。

对于 $j > p_i+s_i$，第 $i$ 盏灯覆盖的范围是 $[2p_i-j,j]$，因而前 $i-1$ 盏灯需要覆盖 $[1,k](2p_i-j-1\leq k\leq j-1)$，$f_{i,j}=j-p_i-s_i+min\{f_{i-1,k}\}$。

注意到 $f_{i,j}$ 只与 $f_{i-1,k}$ 有关，因而可以滚动 $i$ 。根据转移方程，发现可以直接用 $f_j$ 表示覆盖 $[1,j]$ 的花费，略去 $i$ 这一维。

复杂度 $O(nm)$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 21:06:29
**/

#include <bits/stdc++.h>

const int MAXN = 80 + 5;
const int MAXM = 100000 + 5;

int N, M;
std::pair<int, int> A[MAXN];
int F[MAXM << 1];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) scanf("%d%d", &A[i].first, &A[i].second);
	std::sort(A + 1, A + N + 1);
	memset(F, 0x3f, sizeof F);
	F[0] = 0;
	for (int i = 1; i <= N; ++i) {
		int p = A[i].first + A[i].second;
		for (int j = 2 * M; j >= 0; --j)
			F[j] = std::min(F[j + 1], F[j]);
		for (int j = p; j <= 2 * M; ++j)
			F[j] = std::min(F[j], j - p + F[std::max(0, 2 * A[i].first - j - 1)]);
	}
	int ans = INT_MAX;
	for (int i = M; i <= M * 2; ++i) ans = std::min(ans, F[i]);
	printf("%d\n", ans);
	return 0;
}
```

## F. [Cheap Robot](https://codeforces.com/contest/1253/problem/F)

### 题意

在 $n$ 个点 $m$ 条边的无向图上，每条边有边权 $w_i$，编号在 $[1,k]$ 的点为“中心点”。现有一辆小车在图上穿梭，其油箱大小为 $t$。若它某时剩余的油为 $s$，则它可以通过所有边权 $w_i\leq s$ 的边，且通过后 $s$ 减少 $w_i$。若小车到达“中心点”，油箱会加满（$s=t$）。有 $q$ 个询问，每次询问小车从中心点 $a_i$ 出发到中心点 $b_i$ 所需的最小油量 $t$ 。 

$k,n\leq 10^5,m\leq 3\times 10^5,w_i\leq 10^9$

### 题解

由于小车的终点为“中心点”，因而小车在路径上的任意点都应该能抵达离它最近的“中心点”。

小车在任意点驶向离它最近的“中心点”不会使结果更劣，因为它可以通过该“中心点”加满油后原路返回，且剩余的油更多（或相等）。

设点 $i$ 与最近的中心点的距离为 $d_i$，可以通过Disjkstra在 $O(m\log{n})$ 求出。具体而言，将 $[1,k]$ 的距离设为 $0$，求达到其他点的最短距离。

设到达点 $i$ 时剩余油量为 $s$。

若 $s < d_i$，则它无法到达终点。

若 $s \geq d_i$，则通过“中心点”加油回到点 $i$ 后 $s=t-d_i$。

如果要通过 $(i,j)$ 从 $i$ 走到 $j$，且满足到达 $j$ 后仍然能到达离 $j$ 最近的中心点，需满足 $s-d_i-w_{i,j}\geq d_j$，整理一下得 $s\geq d_i+d_j+w_{i,j}$。

因而对于一条 $a_i$ 到 $b_i$ 的路径，需满足初始油量 $t\geq max\{d_i+d_j+w_{i,j}\}$ 。

最小化 $t$，即最小化 $d_i+d_j+w_{i,j}$。将原图的所有边$(u,v)$ 权值重置为 $d_u+d_v+w_{u,v}$ ，然后构造最小生成树，如此使得任意两点间的最大距离最小。

构造完最小生成树后，$t$ 为树上两点边权的最大值，可以用倍增求得。

复杂度 $O(m\log{n}+m\log{m})$。

### 参考代码

```cpp
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
```

