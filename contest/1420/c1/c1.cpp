/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-24 22:52:44
 * Url: https://codeforces.com/contest/1420/problem/C1
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int T, N, Q;
int A[MAXN];
long long F[MAXN][2];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &Q);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		F[1][1] = A[1], F[1][0] = 0;
		for (int i = 2; i <= N; ++i) {
			F[i][0] = max(F[i - 1][0], F[i - 1][1] - A[i]);
			F[i][1] = max(F[i - 1][1], F[i - 1][0] + A[i]);
		}
		printf("%lld\n", max(F[N][0], F[N][1]));
	}
	return 0;
}
