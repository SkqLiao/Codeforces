/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-27 23:10:05
 * Url: https://codeforces.com/contest/1417/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N, M, A[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		if (M % 2 == 1) {
			for (int i = 1; i <= N; ++i) {
				if (A[i] * 2 > M) printf("1 ");
				else printf("0 ");
			}
			puts("");
			continue;
		}
		int cnt = 0;
		for (int i = 1; i <= N; ++i)
			if (A[i] == M / 2) ++cnt;
		cnt /= 2;
		for (int i = 1; i <= N; ++i) {
			if (A[i] * 2 > M) printf("1 ");
			else if (A[i] * 2 < M) printf("0 ");
			else if (cnt-- > 0) printf("1 ");
			else printf("0 ");
		}
		puts("");
	}
	return 0;
}
