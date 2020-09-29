/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-24 23:34:20
 * Url: https://codeforces.com/contest/1420/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
const int MOD = 998244353;

int N, K, L[MAXN], R[MAXN];
vector<int> v;
int A[MAXN << 1][2];
long long Inv[MAXN], Fac[MAXN], P;

int getID(int x) {
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

long long C(int n) {
	if (K > n) return 0;
	return Fac[n] * P % MOD;
}

long long poww(long long x, int t) {
	long long y = 1;
	for (; t; t >>= 1, x = x * x % MOD) {
		if (t & 1) y = y * x % MOD;
	}
	return y;
}

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; ++i) {
		scanf("%d%d", &L[i], &R[i]);
		v.push_back(L[i]);
		v.push_back(R[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i <= N; ++i) {
		A[getID(L[i])][0]++;
		A[getID(R[i]) + 1][1]++;
	}
	Inv[0] = Inv[1] = 1;
	Fac[0] = Fac[1] = 1;
	for (int i = 2; i <= N; ++i) {
		Inv[i] = (MOD - MOD / i) * Inv[MOD % i] % MOD;
		if (i >= K) Fac[i] = Fac[i - 1] * i % MOD * Inv[i - K] % MOD;
		else Fac[i] = Fac[i - 1] * i % MOD;
	}
	P = poww(Fac[K], MOD - 2);
	int total = 0;
	long long ans = 0;
	for (int i = 1; i <= N * 2; ++i) {
		total -= A[i][1];
		ans = (ans - C(total) + MOD) % MOD;
		total += A[i][0];
		ans = (ans + C(total)) % MOD;
	}
	printf("%lld\n", ans);
	return 0;
}
