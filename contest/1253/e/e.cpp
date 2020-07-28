/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 21:06:29
**/
 
#include <bits/stdc++.h>
 
const int MAXN = 80 + 5;
const int MAXM = 100000 + 5;
 
int N, M;
std::pair<int, int> A[MAXN];
int F[MAXN][MAXM << 1];
 
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) scanf("%d%d", &A[i].first, &A[i].second);
	std::sort(A + 1, A + N + 1);
	memset(F, 0x3f, sizeof F);
	F[0][0] = 0;
	for (int i = 1; i <= N; ++i) {
		int p = A[i].first + A[i].second;
		for (int j = p - 1; j >= 0; --j)
			F[i][j] = std::min(F[i][j + 1], F[i - 1][j]);
		for (int j = p; j <= 2 * M; ++j)
			F[i][j] = std::min(F[i - 1][j], j - p + F[i][std::max(0, 2 * A[i].first - j - 1)]);
	}
	int ans = INT_MAX;
	for (int i = M; i <= M * 2; ++i) ans = std::min(ans, F[N][i]);
	printf("%d\n", ans);
	return 0;
}