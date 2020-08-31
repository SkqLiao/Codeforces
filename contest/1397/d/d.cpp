/* Code Information
 * Author: Skqliao
 * Time: 2020-08-30 23:02:01
 * Url: https://codeforces.com/contest/1397/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;

int T, N, A[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		int sum = 0, mx = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) scanf("%d", &A[i]);
		for (int i = 0; i < N; ++i) sum += A[i], mx = max(mx, A[i]);
		if (mx * 2 > sum) {
			puts("T");
		} else {
			puts(sum % 2 ? "T" : "HL");
		}
	}
	return 0;
}
