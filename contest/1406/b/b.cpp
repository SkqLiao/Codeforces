/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 21:52:23
 * Url: https://codeforces.com/contest/1406/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N;
long long A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		sort(A + 1, A + N + 1);
		long long ans1 = A[1] * A[2] * A[3] * A[4] * A[N];
		long long ans2 = A[1] * A[2] * A[N - 2] * A[N - 1] * A[N];
		long long ans3 = A[N] * A[N - 1] * A[N - 2] * A[N - 3] * A[N - 4];
		cout << max(ans1, max(ans2, ans3)) << endl;
	}
	return 0;
}
