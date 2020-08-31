/* Code Information
 * Author: Skqliao
 * Time: 2020-08-22 19:45:53
 * Url: https://codeforces.com/contest/1401/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N, A[MAXN], B[MAXN];
vector<int> v, v2;

void solve() {
	v.clear(); v2.clear();
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
	memcpy(B, A, sizeof(int) * N);
	int mn = A[0];
	for (int i = 1; i < N; ++i) mn = std::min(mn, A[i]);
	for (int i = 0; i < N; ++i) if (A[i] % mn == 0) v.push_back(i);
	sort(B, B + N);
	for (int i = 0; i < N; ++i) if (B[i] % mn == 0) v2.push_back(i);
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i] != v2[i]) {
			puts("NO");
			return ;
		}
	}
	for (int i = 0; i < N; ++i) {
		if (A[i] % mn != 0 && A[i] != B[i]) {
			puts("NO");
			return ;
		}
	}
	puts("YES");
}

int main() {
	scanf("%d", &T);
	while (T--) solve();
	return 0;
}
