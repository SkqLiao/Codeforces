/* Code Information
 * Author: Skqliao
 * Time: 2020-07-24 20:54:20
**/

#include <bits/stdc++.h>
 
const int MAXN = 1e5 + 5;
 
int T, N, A[MAXN];
 
bool solve() {
	int cnt = 0, tmp;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &tmp);
		A[i] -= tmp;
	}
	for (int i = 1; i <= N; ++i) {
		if (A[i] > 0) return false;
		if (A[i] != A[i - 1] && A[i]) ++cnt;
	}
	return cnt <= 1;
}
 
int main() {
	scanf("%d", &T);
	while (T--)
		puts(solve() ? "YES" : "NO");
	return 0;
}