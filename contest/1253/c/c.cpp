/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 11:30:12
**/

#include <bits/stdc++.h>

const int MAXN = 200000 + 5;

int N, M;
long long A[MAXN], B[MAXN];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
	std::sort(A + 1, A + N + 1);
	long long total = 0;
	for (int i = 1, cur = 0; i <= N; ++i, (cur += 1) %= M) {
		total += A[i] + B[cur];
		printf("%lld ", total);
		B[cur] += A[i];
	}
	return 0;
}
