# Codeforces Round #670 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1406)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/82560)

## 比赛状况

Solved: 3/5

Rank: 452

Rating change: +254 -> 1647

## A. [Subset Mex](https://codeforces.com/contest/1406/problem/A)

### 题意

$T$ 组数据，每次输入 $N$ 个数，将其分成两部分 $A, B$，使得 $mex(A)+mex(B)$ 最大，并输出这个最大值。

$T,N\leq 100$

### 题解

从 $0$ 开始将数依次插入集合 $A$ 中，遇到断点后停下，即为 $mex(A)$，剩下的数求 $mex(B)$。

复杂度 $O(N)$。

多组数据记得`memset`。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 21:45:44
 * Url: https://codeforces.com/contest/1406/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;

int T, N, A[MAXN];
int Cnt[MAXN];

int main() {
	cin >> T;
	while (T--) {
		int ans = 0, mx = 0;
		cin >> N;
		memset(Cnt, 0, sizeof Cnt);
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = 1; i <= N; ++i) ++Cnt[A[i]];
		for (int i = 1; i <= N; ++i) mx = max(mx, A[i]);
		for (int i = 0; i <= mx + 1; ++i) {
			if (!Cnt[i]) {
				ans = i;
				break;
			}
			--Cnt[i];
		}
		for (int i = 0; i <= mx + 1; ++i) {
			if (!Cnt[i]) {
				ans += i;
				break;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

## B. [Maximum Product](https://codeforces.com/contest/1406/problem/B)

### 题意

$T$ 组数据，每次输入 $N$ 个数 $A[1\cdots N]$，从中选出 $5$ 个数，使得乘积最大，并输出这个乘积。

$T\leq 2\cdot 10^4,5\leq N\leq 10^5,-3\times 10^3\leq A_i\leq 3\times 10^3$，保证 $\sum{N}\leq 2\cdot 10^5$。

### 题解

只有几种可能取到最大值：

- 最大的五个正数相乘
- 最小的四个负数与最大的正数相乘
- 最小的两个负数与最大的三个正数相乘

可能会存在没有那么多负数/正数的情况，但显然这三种情况至少会满足一种，因此取三种情况的最大值。

复杂度 $O(T\times N)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 21:52:23
 * Url: https://codeforces.com/contest/1406/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N;
long long A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		sort(A + 1, A + N + 1);
		long long ans1 = A[1] * A[2] * A[3] * A[4] * A[N];
		long long ans2 = A[1] * A[2] * A[N - 2] * A[N - 1] * A[N];
		long long ans3 = A[N] * A[N - 1] * A[N - 2] * A[N - 3] * A[N - 4];
		cout << max(ans1, max(ans2, ans3)) << endl;
	}
	return 0;
}
```

## C. [Link Cut Centroids](https://codeforces.com/contest/1406/problem/C)

### 题意

$T$ 组数据，输入一棵 $N$ 个点的树。选择一条边删去，并连接一条新边，要求操作后仍然是一棵树，且只有一个重心。输出删除与增加的边上的两个节点。

$T\leq 10^4,N\leq 10^5$

### 题解

只有当 $N$ 为偶数的时候才可能有两个重心，因而 $N$ 为奇数时可以不改变树的形态。

设两个重心为 $u,v$。将 $u,v$ 的其他子树简化为 $A, B$，则树的形态为 $A-u-v-B$。

由于 $u,v$ 都是重心，因此 $size(A)=\frac{N}{2}-1,size(B)=\frac{N}{2}-1$。

将 $A$ 中一个叶子 $x$ 断开并与 $v$ 相连，此时 $size(u+x+B)>\frac{N}{2}$，因而 $u$ 不再是重心。而对于 $v$ 来说，$size(A+u-x),size(x),size(B)\leq \frac{N}{2}$，仍是重心。而如果对于 $B$ 中的点来说， $size(A+u+v+x) > \frac{N}{2}$，因此不会是新的重心。

复杂度 $O(T\times N)$。

### 参考代码

```cpp
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
```

## D. [Three Sequences](https://codeforces.com/contest/1406/problem/D)

### 题意

输入一个序列 $A[1\cdots N]$，构造出单点不减的序列 $B$ 和单调不升的序列 $C$，满足 $A[i]=B[i]+C[i]$。要使得 $max(B[i],C[i])$ 最小。

有 $Q$ 次修改，每次输入`l r x`，即将 $A[l,r]$ 增加 $x$，求修改后最小的 $max(B[i],C[i])$。

$N,Q\leq 10^5$

### 题解

先尝试用 $B[i]$ 和 $A[i]$ 来表示 $C[i]$，显然 $C[1]=A[1]-B[1]$。

若 $A[2] > A[1]$，由于 $C$ 单调不升，因而 $B[2]=A[2]-C[1]=A[2]-A[1]+B[1],C[2]=C[1]=A[1]-B[1]$。

若 $A[2] < A[1]$，由于 $B$ 单调不降，因而 $C[2]=A[2]-B[1],B[2]=B[1]$。

通过观察即可发现，$B[i]=A[1]+\sum{max(0,A[i]-A[i-1])}-B[1]$。

而所谓的 $max(B[i],C[i])$ 即 $max(B[N],C[1])=max(A[1]+\sum{max(0,A[i]-A[i-1])}+B[1],A[1]-B[1])$。

使最大值最小，则 $A[1]+\sum{max(0,A[i]-A[i-1])}+B[1]=A[1]-B[1]$，得到 $\frac{A[1]+\sum{max(0,A[i]-A[i-1])}}{2}$。

$max(0, A[i]-A[i-1])$ 可以 $O(N)$ 求出。

而对于每次修改，只影响 $max(A[l]-A[l-1],0)$ 和 $max(A[r+1]-A[r],0)$ ，可以 $O(1)$ 修改。

复杂度 $O(N+Q)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 22:22:08
 * Url: https://codeforces.com/contest/1406/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N, M;
long long A[MAXN], sum;

void change(int p, int x) {
	if (p > N) return ;
	if (A[p] > 0) sum -= A[p];
	A[p] += x;
	sum += max((long long)0, A[p]);
}

int main() {
	int l, r, x;
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = N; i >= 1; --i) A[i] -= A[i - 1];
	for (int i = 2; i <= N; ++i) sum += max((long long)0, A[i]);
	cout << (long long)ceil((sum + A[1]) / 2.0) << endl;
	cin >> M;
	while (M--) {
		cin >> l >> r >> x;
		if (l == 1) A[1] += x;
		else change(l, x);
		change(r + 1, -x);
		cout << (long long)ceil((sum + A[1]) / 2.0) << endl;
	}
	return 0;
}
```

## E. [Deleting Numbers](https://codeforces.com/contest/1406/problem/E)

### 题意

这是一道交互题。

输入 $N$，有一个目标数 $M(1\leq M \leq  N)$。初始化集合 $\{1,2,\cdots,N\}$，用三种交互方式：

- `A x`：查询集合中有多少个 $x$ 的倍数。
- `B x`：查询集合中有多少个 $x$ 的倍数，并删去所有 $x$ 的倍数（$M$ 除外）
- `C x`：告知 $M$ 的值为 $x$，结束交互。

交互至多 $10000$ 次。

$N\leq 10^5$

### 题解

将 $M$ 质因数分解为 $\prod{p_i^{a_i}}$。

对于 $p_i\leq \sqrt{M}$，$a_i \geq 1$，而对于 $p_i > \sqrt{M}$，$a_i=1$。

用欧拉筛筛出 $[2,N]$ 的所有质数，对于 $p_i\leq \sqrt{M}$，可以先通过`B x` 删去其所有倍数，再用`A x` 判断 $M$ 是否为 $x$ 的倍数，并从 $1$ 向上枚举幂，直到 $M$ 不是 $p_i^{a_i+1}$ 的倍数，从而得到 $a_i$。

而对于 $p_i > \sqrt{M}$，如果也这么做，势必会超过 $10000$ 次的限制。

但是考虑到 $a_i=1$，且最多只有一个 $p_i > \sqrt{M}$，可以采取分块的方法。

定义块大小为 $B$，先查询 `A 1`，得到当前集合的大小 $num_1$，再连续 `B x` 删除掉 $B$ 个质数的倍数，并得到应该（不考虑 $M$）被删除的个数 $num_2$。再查询 `A 1`，得到集合中实际剩余的个数 $num_3$。

如果 $p_i$ 属于这个块，那么 $num_1-num_3\not = num_2$，再挨个 `A x` 判断是否为 $1$ 即可得到 $p_i$。

### 简易交互器

假设选手代码为 `a.cpp`，交互库为 `b.cpp`，则可以这样实现自动交互：

```shell
g++ a.cpp -o a -O2
g++ b.cpp -o b -O2
(./b < /dev/fd/3 | ./a) 3>&1 | :
```

如果要看到额外的调试信息，可将其以输出到 `stderr`。

### 参考代码

#### 选手

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-13 12:53:11
 * Url: https://codeforces.com/contest/1406/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N, P = 1;
vector<int> Pri;
bitset<MAXN> isnPri;

void getPrime() {
    for (int i = 2; i <= N; ++i) {
        if (!isnPri[i]) Pri.push_back(i);
        for (auto u : Pri) {
            int x = i * u;
            if (x > N) break;
            isnPri.set(x);
            if (i % u == 0) break;
        }
    }
}

int num;

int checkA(int x) {
    printf("A %d\n", x); fflush(stdout);
    scanf("%d", &num);
    return num;
}

int checkB(int x) {
	printf("B %d\n", x); fflush(stdout);
    scanf("%d", &num);
    return num;
}

int get(int x) {
    checkB(x);
	int ans = 1;
    for (int c = x; c * P <= N; c *= x) {
        if (!checkA(c)) break;
		ans *= x;
    }
	return ans;
}

int main() {
	scanf("%d", &N);
    if (N == 1) {
        puts("C 1");
        return 0;
    }
    getPrime();
    int r = -1;
    for (int i = 0; Pri[i] * Pri[i] <= N; ++i) P *= get(Pri[r = i]);
    int sz = sqrt(Pri.size() - r), num = checkA(1);
    for (int i = r + 1, cnt = 0; i < Pri.size(); ++i) {
        num -= checkB(Pri[i]);
        if (++cnt == sz || i == Pri.size() - 1) {
            int nnum = checkA(1);
            if (nnum != num) {
                for (int j = i - cnt + 1; j <= i; ++j) {
                    if (checkA(Pri[j])) {
                        P *= Pri[j];
                        break;
                    }
                }
                break;
            }
            num = nnum;
            cnt = 0;
        }
    }
    printf("C %d\n", P); fflush(stdout);
    return 0;
}
```

#### 交互库

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000 + 5;

int N, M;
int Vis[MAXN];
int cnt, x;
char ch;

int main() {
    scanf("%d%d", &N, &M);
    printf("%d\n", N);
    fprintf(stderr, "%d\n", N);
    fflush(stdout);
    cnt = N;
    while (scanf("%c %d", &ch, &x)) {
        if (ch == 'A' || ch == 'B') {
            if (x == 1) {
                fprintf(stderr, "%c %d\n", ch, x);
                printf("%d\n", cnt);
                fprintf(stderr, "%d\n", cnt);
                fflush(stdout);
                continue;
            }
            int total = 0;
            for (int i = x; i <= N; i += x) {
                total += !Vis[i];
            }
            printf("%d\n", total);
            fprintf(stderr, "%d\n", total);
            if (total < 10) {
                for (int i = x; i <= N; i += x) {
                    if (!Vis[i]) fprintf(stderr, "%d ", i);
                }
                fprintf(stderr, "\n");
            }
            fflush(stdout);
        }
        if (ch == 'B') {
            for (int i = x; i <= N; i += x) {
                if (i != M) Vis[i] = 1;
            }
            cnt = 0;
            for (int i = 1; i <= N; ++i) cnt += !Vis[i];
        }
        if (ch == 'C') {
            cerr << M << " vs " << x << endl;
            break;
        }
    }
    return 0;
}
```