# Codeforces Round #667 (Div. 3) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1409)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/82284)

## 比赛状况

Solved: 6/6

Rank: 53

Rating change: +727 -> 727

## A. [Yet Another Two Integers Problem](https://codeforces.com/contest/1409/problem/A)

### 题意

$T$ 组数据，每次输入 $a$ 和 $b$。求至少多少次操作可以将 $a$ 转化为 $b$。一次操作指的是 $a:=a\pm k(k\in[1,10])$。

$T\leq 2\cdot 10^4,1\leq a,b\leq 10^9$

### 题解

显然尽可能先用 $10$，最后处理一下剩余的部分。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:35:20
 * Url: https://codeforces.com/contest/1409/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T, a, b;
	cin >> T;
	while (T--) {
		cin >> a >> b;
		cout << (abs(a - b) / 10 + (abs(a - b) % 10 != 0)) << endl;
	}
	return 0;
}
```

## B. [Minimum Product](https://codeforces.com/contest/1409/problem/B)

### 题意

$T$ 组数据，每次输入 $a,b,x,y,n$，每次可以选择 $a$ 或 $b$ 将其减一，但必须时刻满足 $a\geq x,b\geq y$，该操作至多进行 $n$ 次。求 $a\cdot b$ 的最小值。

$T\leq 2\cdot 10^4,1\leq a,b,x,y,n\leq 10^9$

### 题解

“和一定，差越小，积越大”，要最小化乘积，就要先将一个数减到最小，然后再减另一个。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:38:02
 * Url: https://codeforces.com/contest/1409/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

long long T, a, b, x, y, n;

long long get(long long a, long long b, long long x, long long y) {
	a -= n;
	if (a < x) {
		b -= (x - a);
		a = x;
	}
	b = max(b, y);
	return a * b;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> a >> b >> x >> y >> n;
		cout << min(get(a, b, x, y), get(b, a, y, x)) << endl;
	}
	return 0;
}
```

## C. [Yet Another Array Restoration](https://codeforces.com/contest/1409/problem/C)

### 题意

有一个未知的长为 $N$ 的等差序列 $A[1\cdots N]$，其中都是正数。已知 $x,y\in A[1\cdots N]$，求 $max(A[1\cdots N])$ 的最小值。

### 题解

枚举 $y-x$ 的因数为公差，然后在保证最小值为正数的前提下将 $x,y$ 尽可能放到最后。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:47:41
 * Url: https://codeforces.com/contest/1409/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

int T, n, x, y, z;

int get(int a) {
	if (z / a + 1 > n) return INT_MAX;
	int mn = x - x / a * a;
	if (!mn) mn += a;
	int num = (y - mn) / a + 1;
	if (num >= n) return y;
	else return y + (n - num) * a;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> x >> y;
		z = y - x;
		int ans = INT_MAX, dv;
		for (int i = 1; i <= sqrt(z) + 1; ++i) {
			if (z % i == 0) {
				int tmp = get(i);
				if (ans > tmp) {
					ans = tmp;
					dv = i;
				}
				tmp = get(z / i);
				if (ans > tmp) {
					ans = tmp;
					dv = z / i;
				}
			}
		}
		for (int i = ans - dv * (n - 1); i <= ans; i += dv) cout << i << " ";
		cout << endl;
	}
	return 0;
}
```

## D. [Decrease the Sum of Digits](https://codeforces.com/contest/1409/problem/D)

### 题意

$T$ 组数据，每次输入一个数 $x$。令 $z=x+y$，求非负数 $y$ 的最小值，满足 $z$ 的各位数字之和不大于 $s$。

$T\leq 2\cdot 10^4,1\leq x\leq 10^{18},1\leq s\leq 162$

### 题解

从个位开始，每次进一位并将该位置为 $0$，直到满足各位数字之和不大于 $s$ 为止。

复杂度 $O(\log{x})$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:06:31
 * Url: https://codeforces.com/contest/1409/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

long long t, x, y;
int len;
char a[20];
int s[20];

int main() {
	cin >> t;
	while (t--) {
		cin >> x >> y;
		sprintf(a, "%lld", x);
		len = strlen(a);
		s[0] = a[0] - '0';
		for (int i = 1; i < len; ++i) s[i] = s[i - 1] + a[i] - '0';
		if (s[len - 1] <= y) {
			cout << 0 << endl;
			continue;
		}
		bool flag = 0;
		for (int i = len - 2; i >= 1; --i) {
			if (a[i] == '9') continue;
			int cur = s[i - 1] + a[i] - '0' + 1;
			if (cur <= y) {
				a[i] += 1;
				for (int j = i + 1; j < len; ++j) a[j] = '0';
				flag = 1;
				break;
			}
		}
		if (!flag) {
			if (a[0] != '9' && a[0] + 1 - '0' <= y) {
				a[0]++;
				for (int i = 1; i < len; ++i) a[i] = '0';
			} else {
				a[0] = '1';
				for (int i = 1; i <= len; ++i) a[i] = '0';
				++len;
			}
		}
		long long z = 0;
		for (int i = 0; i < len; ++i) z = z * 10 + a[i] - '0';
		cout << z - x << endl;
	}
	return 0;
}
```

## E. [Two Platforms](https://codeforces.com/contest/1409/problem/E)

### 题意

$T$ 组数据，输入 $N$ 个点的坐标 $(x_i,y_i)$，以及 $K$。可以选择任意两个横坐标 $x_a,x_b$，则横坐标位于 $[x_a,x_a+K]$ 和 $[x_b,x_b+K]$ 的所有点会被收集。求最多收集多少个点。

$T\leq 2\cdot 10^4,\sum{N}\leq 2\cdot 10^5,K\leq 10^5,1\leq x_i\leq 10^9$

### 题解

对坐标离散化，预处理出所有 $[x_i,x_i+K]$ 的点个数 $P_i$。从左往右枚举 $x_a$，然后算出 $[x_a+K,+\infin]$ 中最大的 $P_i$ 对应 $[x_b,x_b+K]$。

复杂度 $O(T\cdot N)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:27:56
 * Url: https://codeforces.com/contest/1409/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int t, n, k;
int x[MAXN], y[MAXN];
int r[MAXN], num[MAXN];
int id[MAXN], ans[MAXN], mx[MAXN];

int get(int a) {
	return upper_bound(x + 1, x + n + 1, a) - x - 1;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> x[i];
		for (int i = 1; i <= n; ++i) cin >> y[i];
		sort(x + 1, x + n + 1);
		memset(num, 0, sizeof num);
		for (int i = 1; i <= n; ++i) {
			if (x[i] == x[i - 1]) id[i] = id[i - 1];
			else id[i] = id[i - 1] + 1;
			++num[id[i]];
		}
		n = unique(x + 1, x + n + 1) - x - 1;
		for (int i = 1; i <= n; ++i) num[i] += num[i - 1];
		for (int i = 1; i <= n; ++i) {
			ans[i] = num[r[i] = get(x[i] + k)] - num[i - 1];
		}
		mx[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			mx[i] = max(mx[i + 1], ans[i]);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			res = max(res, ans[i] + mx[r[i] + 1]);
		}
		cout << res << endl;
	}
	return 0;
}
```

## F. [Subsequences of Length Two](https://codeforces.com/contest/1409/problem/F)

### 题意

输入母串 $S$ 和子串 $T$，以及整数 $K$。要求修改 $S$ 的至多 $K$ 位，使得 $S$ 的与 $T$ 相同的子序列的数量最大。

$K\leq |S|\leq 200, |T|=2$

### 题解

定义 $F[i][j][k]$ 表示 $S$ 的前 $i$ 位，进行了 $j$ 次修改，当前有 $k$ 个 $T[0]$ 的子序列为 $T$ 的数量，然后转移即可。

复杂度 $O(|S|^2\cdot K)$。

### 参考代码

```cpp
/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:50:14
 * Url: https://codeforces.com/contest/1409/problem/F
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200 + 5;

int N, K;
string s, t;
int f[MAXN][MAXN][MAXN];
bool b[MAXN][MAXN][MAXN];

int main() {
	cin >> N >> K >> s >> t;
	s = "0" + s;
	if (t[0] == t[1]) {
		int num = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			if (s[i] == t[0]) ++num;
		}
		num = min(num + K, N);
		cout << num * (num - 1) / 2 << endl;
	} else {
		b[0][0][0] = 1;
		for (int i = 1; i <= N; ++i) {
			for (int j = 0; j <= min(i, K); ++j) {
				for (int k = 0; k <= i; ++k) {
					if (s[i] == t[1] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k] + k);
						b[i][j][k] = 1;
					}
					if (s[i] != t[1] && b[i - 1][j - 1][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + k);
						b[i][j][k] = 1;
					}
					if (s[i] != t[1] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
						b[i][j][k] = 1;
					}
					if (s[i] == t[0] && b[i - 1][j][k - 1]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1]);
						b[i][j][k] = 1;
					}
					if (s[i] != t[0] && b[i - 1][j - 1][k - 1]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1]);
						b[i][j][k] = 1;
					}
					if (s[i] != t[0] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
						b[i][j][k] = 1;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i <= K; ++i) {
			for (int j = 0; j <= N; ++j) {
				ans = max(ans, f[N][i][j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

