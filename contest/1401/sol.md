# Codeforces Round #665 (Div. 2) 解题报告

## 相关链接

- 比赛链接：[Dashboard](https://codeforces.com/contest/1401)

- 官方题解：[Editorial](https://codeforces.com/blog/entry/81700)

## A. [Distance and Axis](https://codeforces.com/contest/1401/problem/A)

### 题意

$T$ 组数据，$O$ 为原点，$A$ 点在 $x=N$ 处，求最少让 $A$ 移动多少，使得x轴上存在点 $B$ 满足 $|OB|=|AB|=K$。

$T\leq 6000,0\leq N,K\leq 10^6$

### 题解

多退少补。

### 参考代码

```cpp
/* Code Information
 * Author: Skqliao
 * Time: 2020-08-22 19:19:00
 * Url: https://codeforces.com/contest/1401/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int T, N, M;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        if (M > N) printf("%d\n", M - N);
        else printf("%d\n", (N - M) & 1);
    }
	return 0;
}
```

## B. [Ternary Sequence](https://codeforces.com/contest/1401/problem/B)

## C. [Mere Array](https://codeforces.com/contest/1401/problem/C)

## D. [Maximum Distributed Tree](https://codeforces.com/contest/1401/problem/D)

## E. [ Divide Square](https://codeforces.com/contest/1401/problem/E)

## F. [Reverse and Swap](https://codeforces.com/contest/1401/problem/F)