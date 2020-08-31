/* Code Information
 * Author: Skqliao
 * Time: 2020-08-30 22:53:09
 * Url: https://codeforces.com/contest/1397/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000 + 5;

int N;
long long A[MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) scanf("%lld", &A[i]);
	if (N == 1) {
		printf("1 1\n%d\n1 1\n0\n1 1\n0\n", -A[1]);
		return 0;
	}
	printf("%d %d\n", 1, N);
	for (int i = 1; i <= N; ++i) {
		long long b = A[i] % (N - 1) * N;
		A[i] -= b;
		printf("%lld ", -b);
	}
	printf("\n%d %d\n", 1, N - 1);
	for (int i = 1; i < N; ++i) {
		printf("%lld ", -A[i]);
	}
	printf("\n%d %d\n%lld\n", N, N, -A[N]);
	return 0;
}
