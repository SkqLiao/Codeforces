/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-27 23:19:44
 * Url: https://codeforces.com/contest/1417/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int T, N, A[MAXN];
int Max[MAXN], Lst[MAXN], Ans[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		memset(Lst, 0, sizeof Lst);
		memset(Max, 0, sizeof Max);
		memset(Ans, 0x3f, sizeof Ans);
		for (int i = 1; i <= N; ++i) {
			Max[A[i]] = max(Max[A[i]], i - Lst[A[i]]);
			Lst[A[i]] = i;
		}
		for (int i = 1; i <= N; ++i) {
			if (Lst[i]) {
				Max[i] = max(Max[i], N - Lst[i] + 1);
			}
		}
		for (int i = 1; i <= N; ++i) {
			if (Lst[A[i]]) {
				Ans[Max[A[i]]] = min(Ans[Max[A[i]]], A[i]);
			}
		}
		int mn = INT_MAX;
		for (int i = 1; i <= N; ++i) {
			mn = min(mn, Ans[i]);
			if (mn > N) printf("-1 ");
			else printf("%d ", mn);
		}
		puts("");
	}
	return 0;
}
