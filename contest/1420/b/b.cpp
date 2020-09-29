/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-24 22:42:00
 * Url: https://codeforces.com/contest/1420/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N, A[MAXN], B[MAXN];
int Lst[MAXN], Num[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(Lst, 0, sizeof Lst);
		memset(Num, 0, sizeof Num);
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		for (int i = 1; i <= N; ++i) {
			B[i] = 31 - __builtin_clz(A[i]);
			Num[i] = Num[Lst[B[i]]] + 1;
			Lst[B[i]] = i;
		}
		long long ans = 0;
		for (int i = 1; i <= N; ++i) {
			ans += Num[Lst[B[i]]] - Num[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
