/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 10:42:18
 * Url: https://codeforces.com/contest/1255/problem/E1
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N;
vector<int> v;

long long cal(int x) {
	long long ans = 0;
	for (size_t i = 0; i < v.size(); i += x) {
		int m = (i + i + x - 1) / 2;
		for (size_t j = i; j < i + x; ++j) {
			ans += abs(v[j] - v[m]);
		}
	}
	return ans;
}

long long solve(int x) {
	long long ans = LLONG_MAX;
	if (x == 1) return -1;
	else {
		int cur = 2;
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
	for (int i = 1, x; i <= N; ++i) {
		scanf("%d", &x);
		if (x) v.push_back(i);
	}
	printf("%lld\n", solve(v.size()));
	return 0;
}
