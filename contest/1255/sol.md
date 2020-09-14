# Codeforces Round #668 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1405)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/82366)

## A. [Changing Volume](https://codeforces.com/contest/1255/problem/A)

### 题意

$T$ 组数据，每次给定整数 $x,y$，每次可以将 $x$ 进行 $-5,-2,-1,+1,+2,+5$ 五种操作，注意 $x$ 在任意时刻都不能是负数。求 $x$ 转化到 $y$ 所需的最少操作数。

$T\leq 1000,x,y\leq 10^9$

### 题解

显然 $x$ 先通过 $\pm5$ 的操作接近 $y$，需要$\lfloor\frac{|x-y|}{5}\rfloor$ 次。现在剩下的是 $\pm|x-y|\%5$ 。可以发现 $\pm1,\pm2$ 需要 $1$ 次操作，而 $\pm3,\pm4$ 都需要两次（$+1+2\ or +5-2\ /\ +2+2\ or +5-1$）。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-31 10:09:52
 * Url: https://codeforces.com/contest/1255/problem/A
**/

#include <bits/stdc++.h>

int T;
int A[] = {0, 1, 1, 2, 2};

int main() {
	int a, b;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &a, &b);
		int c = abs(a - b);
		printf("%d\n", c / 5 + A[c % 5]);
	}
	return 0;
}
```

## B. [Fridge Lockers](https://codeforces.com/contest/1255/problem/B)

### 题意

有 $n$ 个点，每个点有权值 $a_i$，在 $i,j$ 间增加一条边的花费为 $a_i+a_j$。位于点 $i$ 和点 $j$ 的人知道边 $(i,j)$ 的密码。如果有位于其他点的人知道连接点 $x$ 所有边的密码，则点 $x$ 就不安全。例如图上有 $2$ 个点 $1,2$ ，有 $1$ 条边 $(1,2)$，则点 $1,2$ 都不安全。

现在要在空有 $n$ 个点的图上增加 $m(m\leq n)$ 条边，求使所有点都安全的最小花费以及连边方案。若无解输出 `-1`。

$n\leq 1000$

### 题解

先考虑什么时候无解。如果要保证每个点都安全，则每个点的度数至少为 $2$，则总边数至少为 $n$。因而 $m < n$ 时无解。

而在题干中的例子可以看出，$n=2$ 时也无解，因为位于点 $1,2$ 的人互相知道对方所有边的密码。

现在考虑如何让花费最小。由于 $m=n$，因此唯一的合法解就是每个点的度数为 $2$。又因为所有边权都为对应的两个点的点权之和，因而我们不要考虑具体连边方法，每个点都要连两条边，所以边权和为两倍的点权和，即 $2\times \sum{a_i}$。

至于连边方案，连接 $(i,i+1)$ 形成一个大环，即是每个点的度数为 $2$ 的合法图。

复杂度 $O(n)$ 。 

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-07-31 10:15:47
 * Url: https://codeforces.com/contest/1255/problem/B
**/

#include <bits/stdc++.h>

const int MAXN = 1000 + 5;

int T, N, M;
int A[MAXN];

void solve() {
	int sum = 0;
	for (int i = 1; i <= N; ++i) sum += 2 * A[i];
	printf("%d\n", sum);
	for (int i = 1; i < N; ++i) printf("%d %d\n", i, i + 1);
	printf("%d %d\n", N, 1);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		if (M < N || N == 2) puts("-1");
		else solve();
	}
	return 0;
}
```

## C. [League of Leesins](https://codeforces.com/contest/1255/problem/C)

### 题意

将 $1,2,\cdots, n$ 的全排列 $p_1,p_2,\cdots,p_n$ 从首项开始每三个分成一组，得到 $(p_1,p_2,p_3),(p_2,p_3,p_4),\cdots,(p_{n-2},p_{n-1},p_n)$。现在将每组中的数以及组之间的顺序打乱，要求还原全排列。

例如原全排列 $(1,3,2,4,5)$ 得到 $(5,2,4)(1,2,3),(4,2,3)$ ，还原可得 $(1,3,2,4,5)$ 或 $(5,4,2,3,1)$（都可以）。

$5\leq n\leq 10^5$

### 题解

观察这 $n-2$ 组中有哪些特殊的数。显然位于原全排列的首尾的两个数只出现 $1$ 次，而位于首尾的第二个数只出现 $2$ 次，其余数出现 $3$ 次。

那么我们不难通过这个性质得到全排列的前两个数 $p_1,p_2$，而同时出现 $p_1,p_2$ 的那个组中余下的数就是 $p_3$，再用 $p_2,p_3$ 得到 $p_4$，依次类推可以得到整个全排列。

我是通过 `map` 来维护不同组的，复杂度 $O(n\log{n})$ 。 

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 00:01:59
 * Url: https://codeforces.com/contest/1255/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair

const int MAXN = 1e5 + 5;

int N;
int Tms[MAXN], Ans[MAXN];
map<pair<int, int>, pair<int, int>> Map;

void add(int a, int b, int c) {
	pair<int, int> x = mp(min(a, b), max(a, b));
	if (Map.find(x) != Map.end()) Map[x] = mp(Map[x].first, c);
	else Map[x] = mp(c, 0);
}

int main() {
	scanf("%d", &N);
	for (int i = 1, a[3]; i <= N - 2; ++i) {
		for (int i = 0; i < 3; ++i) {
			scanf("%d", &a[i]);
			++Tms[a[i]];
		}
		sort(a, a + 3);
		for (int i = 0; i < 3; ++i) add(a[i], a[(i + 1) % 3], a[(i + 2) % 3]);
	}
	for (int i = 1; i <= N; ++i)
		if (Tms[i] == 1) Ans[1] = i;
	for (int i = 1; i <= N; ++i)
		if (Tms[i] == 2 && Map.find(mp(min(Ans[1], i), max(Ans[1], i))) != Map.end()) Ans[2] = i;
	Ans[3] = Map[mp(min(Ans[1], Ans[2]), max(Ans[1], Ans[2]))].first;
	for (int i = 4; i <= N; ++i) {
		pair<int, int> x = Map[mp(min(Ans[i - 2], Ans[i - 1]), max(Ans[i - 2], Ans[i - 1]))];
		if (x.first == Ans[i - 3]) Ans[i] = x.second;
		else Ans[i] = x.first;
	}	
	for (int i = 1; i <= N; ++i) printf("%d ", Ans[i]);
	return 0;
}
```

## D. [Feeding Chicken](https://codeforces.com/contest/1255/problem/D)

### 题意

$T$ 组数据。在 $r\times c$ 的矩形中，有若干个格子为 `R`，其余格子为`.`。其中有 $k$ 只鸡，每只鸡的活动区域是个连通块，交集为空，并集为整个矩形。

要求最小化任意两只鸡活动区域中 `R` 的个数之差，给出一个每只鸡的活动区域的合法解。

$T\leq 100, r,c\leq 100$

### 题解

贪心的想，平均分配 `R` 可以使差最小。具体而言，若有 $p$ 个 `R` ，则有 $p\bmod k$ 只鸡有 $\lceil\frac{p}{k}\rceil$ 个 `R`，其余的鸡有 $\lfloor{\frac{p}{k}}\rfloor$ 个 `R`，如此，差为 $0$ 或 $1$（取决于 $p$ 是否为 $k$ 的整数倍）。

那么如何构造解？有两种简单的方法，一是“S”形，二是“回”形。两种方法都可以保证每只鸡的活动区域是一个连通块。

沿着形状走，将格子置为当前鸡的活动区域，直到超过要求个 `R` 时，再转移到下一只鸡。

复杂度 $O(T\times r\times c)$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 10:02:12
 * Url: https://codeforces.com/contest/1255/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;
const int Dicx[] = {0, 1, 0, -1};
const int Dicy[] = {1, 0, -1, 0};

int T, N, M, P;
string S[MAXN];
char D[MAXN][MAXN];

char getX(int x) {
	if (x < 26) return 'A' + x;
	else if (x < 52) return 'a' + x - 26;
	else return x - 52 + '0';
}

bool check(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M && !D[x][y];
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> M >> P;
		for (int i = 0; i < N; ++i) cin >> S[i];
		int total = 0;
		for (int i = 0; i < N; ++i) 
			for (int j = 0; j < M; ++j)
				total += S[i][j] == 'R';
		int num = total % P, cnt = total / P;
		int cx = 0, cy = 0, pos = 0, cur = 0, dir = 0, step = 0;
		memset(D, 0, sizeof D);
		while (step < N * M) {
			++step;
			if (S[cx][cy] == 'R' && cur == cnt + (pos < num)) pos += 1, cur = 0;
			cur += S[cx][cy] == 'R';
			D[cx][cy] = getX(pos);
			if (!check(cx + Dicx[dir], cy + Dicy[dir])) dir = (dir + 1) % 4;
			cx += Dicx[dir], cy += Dicy[dir];
		}
		for (int i = 0; i < N; ++i) cout << D[i] << "\n";
	}
	return 0;
}
```

## E1. [ Send Boxes to Alice (Easy Version)](https://codeforces.com/contest/1255/problem/E1)

### 题意

一排有 $n$ 个盒子，第 $i$ 个盒子有 $a[i]$ 个球。每次可以将位于第 $i$ 个盒子里的球移动到第 $i-1$ 或第 $i+1$ 个盒子中，花费的时间为被移动的球的个数。要求最终每个盒子中的球个数都是某个数 $k(k>1)$ 的倍数（或者为空），求最小时间。

$n\leq 10^5,0\leq a[i]\leq 1$

### 题解

$k$ 的值只能为 $\sum{a[i]}$ 的质因数（显然质因数比其倍数更优）。由于盒子中要么只有 $1$ 个球，要么没有，因此具体移动方法为：将每相邻 $k$ 个有球的盒子里的球移动到中间的那个盒子。取每个 $k$ 对应时间的最小值。

复杂度 $O(n\times\omega{(n)})$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 10:42:18
 * Url: https://codeforces.com/contest/1255/problem/E1
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N;
vector<int> v;

long long cal(int x) {
	long long ans = 0;
	for (size_t i = 0; i < v.size(); i += x) {
		int m = (i + i + x - 1) / 2;
		for (size_t j = i; j < i + x; ++j) {
			ans += abs(v[j] - v[m]);
		}
	}
	return ans;
}

long long solve(int x) {
	long long ans = LLONG_MAX;
	if (x == 1) return -1;
	else {
		int cur = 2;
		while (cur * cur <= x) {
			if (x % cur == 0) ans = min(ans, cal(cur));
			while (x % cur == 0) x /= cur;
			++cur;
		}
		if (x > 1) ans = min(ans, cal(x));
	}
	return ans;
}

int main() {
	scanf("%d", &N);
	for (int i = 1, x; i <= N; ++i) {
		scanf("%d", &x);
		if (x) v.push_back(i);
	}
	printf("%lld\n", solve(v.size()));
	return 0;
}
```

## E2. [Send Boxes to Alice (Hard Version)](https://codeforces.com/contest/1255/problem/E2)

### 题意

在E1的基础上减少了限制：$n\leq 10^6,0\leq a[i]\leq 10^6$。

### 题解

与E1相同，$k$ 的值仍然只能是 $\sum{a[i]}$ 的质因数。

假设处理完了前 $n-1$ 个盒子，现在到第 $n$ 个。有两种处理方法，一是将$\sum\limits_{i=1}^{n}{a_i}\bmod k$ 个球挪到第 $n+1$ 个盒子，或是将 $k-\sum\limits_{i=1}^{n}{a_i}\bmod k$ 个球从第 $n+1$ 个盒子挪到第 $n$ 个盒子。虽然我们不知道前 $n$ 个盒子中球的具体放置方法，但是若每个盒子中的球都是 $k$ 的倍数，其球的总数也得是 $k$ 的倍数，因而需要将多余的球向右挪走，或者将缺少的球从右补充。

无论选择哪一种，前 $n$ 个盒子的问题都已解决，且对后面的盒子都没有影响，因而当前操作选择两个方法中时间较短的那个。

为什么对右边没有影响？假设 $\sum\limits_{i=1}^{n}{a_i}\bmod k =p$，若使用方法一，$a[n+1]:=a[n+1]+p$；若使用方法二，$a[n+1]:=a[n+1]-k+p$，而增加或减少 $k$ 个球对其不会产生影响，因为$a[n+1] \bmod k$ 不变。

复杂度 $O(n\times\omega{(n)})$。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 12:52:44
 * Url: https://codeforces.com/contest/1255/problem/E2
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int N, A[MAXN];

long long cal(long long x) {
	long long ans = 0, cur = 0;
	for (int i = 1; i <= N; ++i) {
		cur = (cur + A[i]) % x;
		ans += min(cur, x - cur);
	}
	return ans;
}

long long solve(long long x) {
	long long ans = LLONG_MAX;
	if (x == 1) return -1;
	else {
		long long cur = 2;
		while (cur * cur <= x) {
			if (x % cur == 0) ans = min(ans, cal(cur));
			while (x % cur == 0) x /= cur;
			++cur;
		}
		if (x > 1) ans = min(ans, cal(x));
	}
	return ans;
}

int main() {
	scanf("%d", &N);
	long long sum = 0;
	for (int i = 1, x; i <= N; ++i) {
		scanf("%d", &A[i]);
		sum += A[i];
	}
	printf("%lld\n", solve(sum));
	return 0;
}
```

## F. [Point Ordering](https://codeforces.com/contest/1255/problem/F)

### 题意

这是一条交互题。

在凸包上有 $n$ 个顶点，不知道每个顶点 $a_i$ 的坐标。

可以通过两种方式询问：

`1 x y z`：返回 $a_x,a_y,a_z$ 为顶点的三角形的面积的二倍。

`2 x y z`：返回$\vec{a_xa_y}$ 与 $\vec{a_xa_z}$ 叉乘结果的符号（$\pm1$）。

保证返回值为整数。

最多可以询问 $3n$ 次。

要求最终从顶点 $1$ 开始，逆时针顺序给出每个顶点编号。

### 题解

首先已知起点是 $1$，可以通过 $n-2$ 次询问得到其逆时针方向的第一个点编号（$p_2$）。

询问`2 1 p2 i`，若返回 $-1$，说明 $i$ 相比当前 $p_2$ 更靠逆时针方向，置 $i$ 为新的 $p_2$。

然后通过 $n-2$ 次询问，得到 $1,p_2$ 与其他每个顶点组成的三角形面积的二倍。

由凸包的形状不难得出，顶点沿着逆时针方向，三角形面积应先变大，再减小。

设面积最大的顶点为 $x$，则通过 $n-3$ 次询问 `1 1 x i` 即可得到点 $i$ 在 $x$ 的顺时针方向还是逆时针方向。

输出 $1,p_2$，然后按照面积从小到大依次输出点 $x$ 顺时针方向的顶点编号，输出 $x$，再按照面积从大到小依次输出点 $x$ 逆时针方向的顶点编号。

总共 $3n-7$ 次询问。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 13:53:16
 * Url: https://codeforces.com/contest/1255/problem/F
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000 + 5;

int N, P[MAXN];
long long D[MAXN];
vector<pair<long long, int>> v, f[2];

int main() {
	scanf("%d", &N);
	P[1] = 1, P[2] = 2;
	for (int i = 3, x; i <= N; ++i) {
		printf("2 1 %d %d\n", P[2], i); fflush(stdout);
		scanf("%d", &x);
		if (x == -1) P[2] = i;
	}
	for (int i = 2; i <= N; ++i) {
		if (i == P[2]) continue;
		printf("1 1 %d %d\n", P[2], i); fflush(stdout);
		scanf("%lld", &D[i]);
		v.push_back(make_pair(D[i], i));
	}
	sort(v.begin(), v.end());
	int p = v.back().second;
	for (int i = 2, x; i <= N; ++i) {
		if (i == p || i == P[2]) continue;
		printf("2 1 %d %d\n", p, i); fflush(stdout);
		scanf("%d", &x);
		f[x == -1].push_back(make_pair(D[i], i));
	}
	sort(f[0].begin(), f[0].end());
	sort(f[1].begin(), f[1].end());
	printf("0 %d %d ", P[1], P[2]);
	for (int i = 0; i < f[1].size(); ++i) printf("%d ", f[1][i].second);
	printf("%d ", p);
	for (int i = f[0].size() - 1; i >= 0; --i) printf("%d ", f[0][i].second);
	fflush(stdout);
	return 0;
}
```