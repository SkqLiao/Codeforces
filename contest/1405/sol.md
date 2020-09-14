# Codeforces Round #668 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1405)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/82366)

## 比赛状况

Solved: 4/5

Rank: 403

Rating change: +448 -> 1175

## A. [Permutation Forgery](https://codeforces.com/contest/1405/problem/A)

### 题意

输入一个长为 $n$ 的全排列 $[p_1,\cdots, p_n]$，定义 $F(p)=sort([p_1+p_2,p_2+p_3,\cdots,p_{n-1}+p_n])$。

输出一个长为 $n$ 的不同于 $p$ 的全排列 $[p'_1,\cdots,p'_n]$，满足 $F(p)=F(p')$。

$n\leq 100$

### 题解

作为div2 A，不可能多复杂。将 $p$ 翻转得到 $p'$，显然满足 $F(p)=F(p')$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 22:35:55
 * Url: https://codeforces.com/contest/1405/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;

int T, N;
int A[MAXN], B[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = N; i >= 1; --i) cout << A[i] << " ";
		cout << endl;
	}
	return 0;
}
```

## B. [Array Cancellation](https://codeforces.com/contest/1405/problem/B)

### 题意

输入一个长为 $n$ 的序列 $[a_1,\cdots,a_n]$，满足 $\sum{a_i}=0$。每次可以选择任意两个位置 $i,j$，使 $a_i:=a_i-1,a_j:=a_j+1$。若 $i < j$，本次操作免费，反之代价为 $1$。

求最小代价使 $\forall a_i=0$。

$n\leq 10^5$

### 题解

显然先尽可能做免费的操作，复杂度 $O(n)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 22:40:54
 * Url: https://codeforces.com/contest/1405/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N;
int A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		long long ans = 0;
		for (int i = 1, j2 = 2; i <= N; ++i) {
			if (A[i] > 0) {
				while (A[i] > 0 && j2 <= N) {
					while (j2 <= i) ++j2;
					while (A[j2] >= 0 && j2 <= N) ++j2;
					int add = min(A[i], -A[j2]);
					A[i] -= add, A[j2] += add;
				}
			}
		}
		for (int i = 1, j = 2; i <= N; ++i) {
			if (A[i] < 0) {
				ans += -A[i];
				while (A[i] < 0) {
					while (j <= i) ++j;
					while (A[j] <= 0 && j <= N) ++j;
					int add = min(-A[i], A[j]);
					A[i] += add, A[j] -= add;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

## C. [Balanced Bitstring](https://codeforces.com/contest/1405/problem/C)

### 题意

$T$ 组数据，每次输入一个字符串 $s$ 和整数 $k$，满足 $\forall s[i]\in \{0,1,?\}$。现要将所有 $?$ 指定为 $0$ 或 $1$，使得新串 $s'$ 满足所有长度为 $k$ 的子串中，各自 $0,1$ 的个数相等。如果不存在输出`-1`。

$T\leq 10^4,|s|,k\leq 3\cdot 10^5$

###  题解

根据题意 $s[1,\cdots,k]$ 和 $s[2,\cdots,k+1]$ 的 $0,1$ 数量各自相同。由于 $s[2,\cdots,k]$ 是相同的，因此 $s[1]=s[k+1]$。推广一下，即 $s[1]=s[k+1]=s[2k+1],s[2]=s[k+2]=s[2k+2]\cdots$。

因而将 $s[1\cdots,n]$ 按照 $\bmod k$ 分组，现在要求每组全部是 $0$ 或全部是 $1$，如果同时出现，那显然无解，输出 `-1`。

那么现在要处理的是全是 $?$ 的组，显然只要 $s[1\cdots,k]$ 确定，$s$ 的所有位就确定了。那么统计 $s[1,\cdots,k]$ 中的 $0,1$ 数量，用 $?$ 去补缺口即可。

复杂度 $O(T\cdot n)$，我为了图方便用了set。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 23:01:08
 * Url: https://codeforces.com/contest/1405/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int T, N, K;
string S;
set<char> V[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> K >> S;
		S = " " + S;
		for (int i = 1; i <= K; ++i) {
			V[i].clear();
			for (int j = i; j <= N; j += K) V[i].insert(S[j]);
		}
		bool flag = 1;
		int cnt = 0;
		for (int i = 1; i <= K; ++i) {
			if (V[i].find('0') != V[i].end() && V[i].find('1') != V[i].end()) {
				flag = 0;
				break;
			}
			if (V[i].find('0') != V[i].end()) {
				for (int j = i; j <= N; j += K) S[j] = '0';
				++cnt;
			} else if (V[i].find('1') != V[i].end()) {
				for (int j = i; j <= N; j += K) S[j] = '1';
			}
		}
		int A[2] = {0, 0};
		for (int i = 1; i <= K; ++i) {
			if (S[i] == '?') {
				if (cnt < K / 2) {
					for (int j = i; j <= N; j += K) S[j] = '0';
					++cnt;
				} else {
					for (int j = i; j <= N; j += K) S[j] = '1';
				}
			}
		}
		for (int i = 1; i <= K; ++i) A[S[i] - '0']++;
		if (A[0] != A[1]) flag = 0;
		for (int i = K + 1; i <= N; ++i) {
			A[S[i - K] - '0']--;
			A[S[i] - '0']++;
			if (A[0] != A[1]) {
				flag = 0;
				break;
			}
		} 
		if (!flag) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
	return 0;
}
```

## D. [Tree Tag](https://codeforces.com/contest/1405/problem/D)

### 题意

Alice和Bob在一棵树上，Alice开始在 $a$ 点，Bob在 $b$ 点。Alice每次可以移动到与当前点距离不超过 $da$ 的任意节点上（可以不动），而Bob的移动范围是 $db$。

Alice和Bob都绝顶聪明，求经过若干轮后Alice能否和Bob在同一点上。如果可以，则 `Alice`，反之输出 `Bob`。

$n\leq 10^5$

### 题解

cf div2D 传统艺能博弈论。

先考虑最简单的情况，若 $a,b$ 距离不超过 $da$，则Alice可以一步到达 $b$ 点，此时Alice必胜。

如果直径不超过 $2\cdot da$，那么Alice可以先移动到直径的中点处，此时无论Bob怎么移动，Alice下一步都能抵达与Bob相同的点，此时Alice必胜。

现在考虑一条链的情况，从左端点依次编号 $1,\cdots, n$。假如Bob在点 $1$，Alice在点 $d$，若 $db>2\cdot d$，$da\leq d$，那么Bob就可以在点 $1$ 和 点 $db+1$ 间反复横跳，Alice永远不可能与Bob到同一点，此时Bob胜。

那么拓展一下，假设没有 $db > 2\cdot d$ 的条件，但仍满足 $db\geq 2\cdot da$。显然若 $2d < db$，Bob可以采取同样的策略。 若 $2d > db$，那么Alice可以每次都更靠近Bob，而Bob只能选择远离Alice的方向，但最后会被卡到端点处，所以若干轮后 $d$ 会满足 $2d < db$，而Bob仍然采取反复横跳的方法，此时Bob胜。

再回到树的一般情况，我们可以把Bob的子树和父亲的子树视作链的左右两个方向，其实质与一条链的情况相同，最后Bob到达叶子节点处，Alice仍然无法追上他，此时Bob胜。

那若 $db < 2 \cdot da$ 呐？显然Bob无法采取因为该方法，因为被卡在叶子节点后，他可以到达的所有节点都在Alice下一步的范围内，因此Alice胜。

总结一下，若 $dis(a,b) \leq da$，或树的直径不超过 $2\cdot da$，或 $2da \geq db$时，Alice胜，反之Bob胜。

复杂度 $O(n)$。

### 参考代码

```cpp
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
```

## E. [Fixed Point Removal](https://codeforces.com/contest/1405/problem/E)

### 题意

输入一个长为 $n$ 的序列 $[a_1,\cdots,a_n]$。每次可以删除满足 $i=a_i$ 的 $a_i$ 。注意到删除 $a_i$ 后，在它后面所有数的下标会改变。序列的“重量”定义为它最多能删去的数的数量。

现有 $q$ 组询问，每次输入 $l,r$，意为初始下标为 $[1,\cdots,l]$ 和 $[n-r+1,\cdots,n]$ 的数不能被删除。求在该情况下序列的“重量”。

$n,q\leq 3\cdot 10^5$

### 题解

令 $b_i=i-a_i$。为了删去尽可能多的数，我们显然会选择从后往前删。若 $a_i$ 前面有不少于 $b_i$ 个数可以被删除，那么 $a_i$ 也能被删除。

对于 $a_i$，求最靠右的左端点 $l_i$，表示仅凭删去 $a[l_i,i]$ 中的数即可使 $a_i$ 能被删除（即 $a_i$ 可在前 $l_i-1$ 个数不能被删除的情况下被删除）。

那么从左往右处理，则 $f_i$ 满足 $[f_i,i]$ 中有恰好 $b_i$ 个标记。可以通过二分+树状数组（$O(\log^2{n})$）或者在线段树二分（$O(\log{n})$）完成。

那么将所有查询按照右端点 $R_i:=n-r_i+1$ 排序，每次插入当前点，并求 $[l_i+1,R_i]$ 中的标记个数。

复杂度 $O(n\log{n})$ 或 $O(n\log^2{n})$。

### 参考代码

####  线段树上二分

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-09 20:24:06
 * Url: https://codeforces.com/contest/1405/problem/E
 * O(N*log(N))
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, M, A[MAXN];
vector<pair<int, int>> V[MAXN];
int Ans[MAXN];
int Sum[MAXN << 2];

void add(int rt, int l, int r, int p) {
    if (l == r) {
        ++Sum[rt];
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) add(rt << 1, l, m, p);
    else add(rt << 1 | 1,m + 1, r, p);
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}

int Bquery(int rt, int l, int r, int x) {
    if (l == r) return l;
    int m = (l + r) >> 1;
    if (Sum[rt << 1 | 1] >= x) return Bquery(rt << 1 | 1, m + 1, r, x);
    else return Bquery(rt << 1, l, m, x - Sum[rt << 1 | 1]);
}

int querySum(int rt, int l, int r, int a, int b) {
    if (a <= l && r <= b) return Sum[rt];
    int m = (l + r) >> 1, sum = 0;
    if (a <= m) sum += querySum(rt << 1, l, m, a, b);
    if (m < b) sum += querySum(rt << 1 | 1, m + 1, r, a, b);
    return sum;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        A[i] = i - A[i];
    }
    for (int i = 1, l, r; i <= M; ++i) {
        cin >> l >> r;
        V[N - r].push_back(make_pair(l + 1, i));
    }
    for (int i = 1; i <= N; ++i) {
        if (A[i] == 0) add(1, 1, N, i);
        else if (A[i] > 0 && Sum[1] >= A[i]) add(1, 1, N, Bquery(1, 1, N, A[i]));
        for (auto u : V[i]) Ans[u.second] = querySum(1, 1, N, u.first, i);
    }
    for (int i = 1; i <= M; ++i) cout << Ans[i] << endl;
    return 0;
}
```

####  二分+树状数组

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-07 00:14:49
 * Url: https://codeforces.com/contest/1405/problem/E
 * O(N*log^2(N))
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, M, A[MAXN];
vector<pair<int, int>> v[MAXN];
int B[MAXN], Ans[MAXN];
int F[MAXN];
int Sum[MAXN];

int lowbit(int x) {
	return x & -x;
}

void add(int pos, int val) {
	for (; pos <= N; pos += lowbit(pos)) Sum[pos] += val;
}

int query(int pos) {
	int val = 0;
	for (; pos; pos -= lowbit(pos)) val += Sum[pos];
	return val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		A[i] = i - A[i];
	}
	for (int i = 1, l, r; i <= M; ++i) {
		cin >> l >> r;
		v[N - r].push_back(make_pair(l + 1, i));
	}
	for (int i = 1; i <= N; ++i) {
		if (A[i] >= 0) {
			int l = 1, r = i, pos = 0;
			while (l <= r) {
				int m = (l + r) >> 1;
				if (query(m) >= A[i]) {
					l = m + 1;
					pos = m;
				} else r = m - 1;
			}
			if (pos) {
				add(1, 1);
				add(pos + 1, - 1);
			}
		}	
		for (auto u : v[i]) Ans[u.second] = query(u.first);
	}
	for (int i = 1; i <= M; ++i) cout << Ans[i] << endl;
	return 0;
}
```

