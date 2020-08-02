/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 12:52:44
 * Url: https://codeforces.com/contest/1255/problem/E2
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int N, A[MAXN];

long long cal(long long x) {
	long long ans = 0, cur = 0;
	for (int i = 1; i <= N; ++i) {
		cur = (cur + A[i]) % x;
		ans += min(cur, x - cur);
	}
	return ans;
}

long long solve(long long x) {
	long long ans = LLONG_MAX;
	if (x == 1) return -1;
	else {
		long long cur = 2;
		while (cur * cur <= x) {
			if (x % cur == 0) ans = min(ans, cal(cur));
			while (x % cur == 0) x /= cur;
			++cur;
		}
		if (x > 1) ans = min(ans, cal(x));
	}
	return ans;
}

int main() {
	scanf("%d", &N);
	long long sum = 0;
	for (int i = 1, x; i <= N; ++i) {
		scanf("%d", &A[i]);
		sum += A[i];
	}
	printf("%lld\n", solve(sum));
	return 0;
}