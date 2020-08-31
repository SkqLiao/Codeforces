/* Code Information
 * Author: Skqliao
 * Time: 2020-08-30 22:39:22
 * Url: 
**/
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e5 + 5;
 
int N, A[MAXN];
 
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &A[i]);
	}
	sort(A, A + N);
	long long ans = LLONG_MAX;
	for (int i = 1; ; ++i) {
		long long cur = 1;
		long long tans = 0;
		for (int j = 0; j < N; ++j) {
			tans += abs(A[j] - cur);
			if (LLONG_MAX / cur < i) {
				if (j == N - 1) ans = min(ans, tans);
				printf("%lld\n", ans);
				return 0;
			}
			cur *= i;
		}
		ans = min(ans, tans);
	}
	return 0;
}