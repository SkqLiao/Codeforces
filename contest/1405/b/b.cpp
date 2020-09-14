/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 22:40:54
 * Url: https://codeforces.com/contest/1405/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int T, N;
int A[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		long long ans = 0;
		for (int i = 1, j2 = 2; i <= N; ++i) {
			if (A[i] > 0) {
				while (A[i] > 0 && j2 <= N) {
					while (j2 <= i) ++j2;
					while (A[j2] >= 0 && j2 <= N) ++j2;
					int add = min(A[i], -A[j2]);
					A[i] -= add, A[j2] += add;
				}
			}
		}
		for (int i = 1, j = 2; i <= N; ++i) {
			if (A[i] < 0) {
				ans += -A[i];
				while (A[i] < 0) {
					while (j <= i) ++j;
					while (A[j] <= 0 && j <= N) ++j;
					int add = min(-A[i], A[j]);
					A[i] += add, A[j] -= add;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
