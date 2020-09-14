# Codeforces Round #669 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1407)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/82417)

## 比赛状况

Solved: 2/5

Rank: 2720

Rating change: +218 -> 1393（第三场base +250，所以实则掉了）

C题交互想歪了，D题由于两行if顺序写反了直接FST，怎一个惨字了得。。

## A. [Ahahahahahahahaha](https://codeforces.com/contest/1407/problem/A)

### 题意

$T$ 组数据，每次输入长为 $N$ 为 01序列 $A[1\cdots N]$，可以删除至多 $\frac{N}{2}$ 个数，要求删除后的新序列满足 $A[1]+A[3]+\cdots=A[2]+A[4]+\cdots$。

输出新序列的长度以及新序列。

$T\leq 10^3,\sum{n}\leq 10^3$，$N$ 为偶数。

### 题解

注意到序列中只有 $0$ 和 $1$，因此必有一个数的数量不超过 $\frac{N}{2}$。将这些数（若个数相等选择删除 $0$）全部删除，则新序列只有 $0$ 或 $1$。若新序列长度为奇数且都由 $1$ 组成，则需要再删去一个 $1$。由此新序列要么都是 $0$，要么由偶数个 $1$ 构成，满足条件。

复杂度 $O(\sum{N})$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 22:35:33
 * Url: https://codeforces.com/contest/1407/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int T, N, A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		int cnt = 0;
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = 1; i <= N; ++i) if (A[i] == 1) ++cnt;
		if (cnt > N / 2) {
			if (cnt % 2) --cnt;
			cout << cnt << endl;
			for (int i = 1; i <= cnt; ++i) cout << 1 << " ";
		} else {
			cout << N - cnt << endl;
			for (int i = 1; i <= N - cnt; ++i) cout << 0 << " ";
		}
		cout << endl;
	}
	return 0;
}
```



## B. [Big Vova](https://codeforces.com/contest/1407/problem/B)

### 题意

$T$ 组数据，每次输出一个长为 $N$ 的序列 $A[1\cdots N]$，可以将其重新排列得到 $B[1\cdots N]$，定义 $C[i]=gcd(B[1],\cdots,B[i])$。现要 $C$ 的字典序最小，求 $B$。

$T,\sum{N},A_i\leq 10^3$

### 题解

字典序是诸位比较，因此可以从第 $1$ 位开始贪心，显然 $C[1]=max(A[i])$。然后暴力找到 $A[i]$ 中 $gcd(A[i],C[1])$ 最大的，插入 $C$ 的末位，然后找到$gcd(A[i],gcd(C[1],\cdots,C[j]))$ 中最大的 $A[i]$，直到插满为止。

复杂度不低，但数据范围很小。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 22:43:39
 * Url: https://codeforces.com/contest/1407/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int T, N, A[MAXN];
int B[MAXN], C[MAXN], D[MAXN];

int main() {
	cin >> T;
	while (T--) {
		memset(B, 0, sizeof B);
		memset(C, 0, sizeof C);
		memset(D, 0, sizeof D);
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		sort(A + 1, A + N + 1, greater<int>());
		int cur = A[1], pos = 2;
		C[1] = A[1], D[1] = 1;
		while (pos <= N) {
			int mx = 0;
			for (int i = 2; i <= N; ++i) {
				if (D[i]) continue;
				B[i] = __gcd(cur, A[i]);
				if (B[i] > B[mx]) mx = i;
			}
			cur = B[mx];
			for (int i = 2; i <= N; ++i) if (B[i] == B[mx]) C[pos++] = A[i], D[i] = 1;
		}
		for (int i = 1; i <= N; ++i) cout << C[i] << " ";
		cout << endl;
	}
	return 0;
}
```

## C. [Chocolate Bunny](https://codeforces.com/contest/1407/problem/C)

### 题意

这是一道交互题。

有一个长为 $N$ 的全排列 $P[1\cdots N]$，要通过至多 $2\cdot N$ 次询问得到它。

- `? x y`：返回 $P[x]\bmod P[y]$

$N\leq 10^4$

### 题解

对于任意两个数 $x,y$，考虑相互取模能得到什么。

若 $x > y$，则 $x\bmod y=p_x,y\bmod x=y$，而 $p_x < y$。

若 $y > x$，则 $x\bmod y=x,y\bmod x=p_y$，而 $p_y < x$。

因而可以得到 $x,y$ 中谁是较小的值，以及值是几，同时也就知道了谁是未知的较大数。

那么可以通过“打擂台”的方式求出这个序列。

每次查询 `? i j` 和 `? j i`，假设 $P[i] > P[j]$，则得到了 $P[j]$ 的值，然后再用同样的方法查询 $i$ 和下一个数。

如此通过 $2\cdot(n-1)$ 次可以得到较小的 $n-1$ 个数的值，由于它是全排列，未出现的数即为剩下数的值。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-09 13:57:53
 * Url: https://codeforces.com/contest/1407/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;

int N, A[MAXN], B[MAXN];

int get(int x, int y) {
    int a, b;
    cout << "? " << x << " " << y << endl;
    cout.flush();
    cin >> a;
    cout << "? " << y << " " << x << endl;
    cin >> b;
    if (a > b) swap(x, y), swap(a, b);
    A[y] = b, B[b] = 1;
    return x;
}

int main() {
    cin >> N;
    if (N == 1) {
        cout << "! 1" << endl; cout.flush();
        return 0;
    }
    int cur = get(1, 2);
    for (int i = 3; i <= N; ++i) cur = get(cur, i);
    for (int i = 1; i <= N; ++i) if (!B[i]) A[cur] = i;
    cout << "! ";
    for (int i = 1; i <= N; ++i) cout << A[i] << " ";
    cout << endl; cout.flush();
    return 0;
}
```

## D. [Discrete Centrifugal Jumps](https://codeforces.com/contest/1407/problem/D)

### 题意

输入长为 $N$ 的序列 $A[1\cdots N]$，从 $1$ 开始跳跃，到 $N$ 结束。

一次合法的从 $i$ 到 $j$ 的跳跃满足以下条件之一：

- $j=i+1$
- $max(A[i],A[j]) < min(A[i+1],\cdots,A[j-1])$
- $min(A[i],A[j]) > max(A[i+1],\cdots,A[j-1])$

求从 $1$ 到 $N$ 最少经过几次跳跃。

### 题解

可以通过单调栈预处理出来 $A[i]$ 左右侧第一个大于等于/小于等于它的数的位置 $Lmax[i],Lmin[i],Rmax[i],Rmin[i]$，那么一次合法的转移即是$Lmin[i]\rightarrow i,Lmax[i]\rightarrow i,i\rightarrow Rmax[i],i\rightarrow Rmin[i]$。

然后从 $1$ 开始DP即可。

复杂度 $O(n)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 23:37:18
 * Url: https://codeforces.com/contest/1407/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, A[MAXN];
int F[MAXN];
stack<int> S;
int Lx[MAXN], Ln[MAXN], Rx[MAXN], Rn[MAXN];

bool check(int x) { return 1 <= x && x <= N; }

bool cmp(int x, int y, bool c) {
	return c ? x >= y : x <= y;
}

void get(int inc, int B[], bool c) {
	while (!S.empty()) S.pop();
	int cur = inc == -1 ? N : 1;
	S.push(cur);
	cur += inc;
	while (check(cur)) {
		if (!S.empty() && cmp(A[cur], A[S.top()], c)) {
			B[S.top()] = cur; S.pop();
		} else {
			S.push(cur);
			cur += inc;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	get(1, Rx, 1); get(1, Rn, 0);
	get(-1, Lx, 1); get(-1, Ln, 0);
	memset(F, 0x3f, sizeof F);
	F[1] = 0;
	for (int i = 1; i <= N; ++i) {
		if (Ln[i])	F[i] = min(F[i], F[Ln[i]] + 1);
		if (Lx[i])	F[i] = min(F[i], F[Lx[i]] + 1);
		if (Rx[i])	F[Rx[i]] = min(F[Rx[i]], F[i] + 1);
		if (Rn[i])	F[Rn[i]] = min(F[Rn[i]], F[i] + 1);
	}
	cout << F[N] << endl;
	return 0;
}
```

## E. [Egor in the Republic of Dagestan](https://codeforces.com/contest/1407/problem/E)

### 题意

输入 $N,M$，给定一张有向图，每条边有边权 $0$ 或 $1$。现要将每个点的点权 $A[i]$ 指定为 $0$ 或 $1$。对于一条边 $(u,v,w)$，如果 $A[u]\not =w$，则不能经过。

要让新图从 $1$ 到 $N$ 的最短路径最长（或无法到达），输出这个距离（无法到达输出`-1`），以及每个点的点权。

$N,M\leq 500000$

### 题解

将原图翻转，即 $(u,v,w)$ 转化为 $(v,u,w)$，则 $A[v]\not =w$ 的边不能经过。

以 $N$ 为起点跑最短路，由于边长为 $1$，故只需要BFS。

令 $F[u][0/1]$ 表示 $u$ 的点权为 $0/1$ 时到 $u$ 的最短路长度，对于所有 $(u,v,w)$，$F[u][0/1]=max(F[v][w])+1$。

答案为 $max(F[1][0],F[1][1])$。

而每个点的点权为 $F[i][0],F[i][1]$ 较大的那个所对应的下标 。

复杂度 $O(N+M)$。

### 参考代码

```cpp
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
```

