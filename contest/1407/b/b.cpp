/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 22:43:39
 * Url: https://codeforces.com/contest/1407/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int T, N, A[MAXN];
int B[MAXN], C[MAXN], D[MAXN];

int main() {
	cin >> T;
	while (T--) {
		memset(B, 0, sizeof B);
		memset(C, 0, sizeof C);
		memset(D, 0, sizeof D);
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		sort(A + 1, A + N + 1, greater<int>());
		int cur = A[1], pos = 2;
		C[1] = A[1], D[1] = 1;
		while (pos <= N) {
			int mx = 0;
			for (int i = 2; i <= N; ++i) {
				if (D[i]) continue;
				B[i] = __gcd(cur, A[i]);
				if (B[i] > B[mx]) mx = i;
			}
			cur = B[mx];
			for (int i = 2; i <= N; ++i) if (B[i] == B[mx]) C[pos++] = A[i], D[i] = 1;
		}
		for (int i = 1; i <= N; ++i) cout << C[i] << " ";
		cout << endl;
	}
	return 0;
}
