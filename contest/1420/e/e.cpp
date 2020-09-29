/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-26 17:37:31
 * Url: https://codeforces.com/contest/1420/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 80 + 5;

int N, A[MAXN];
int F[MAXN][MAXN][MAXN * MAXN / 2];
int Pos[MAXN];

int cal(int x) {
	return x * (x - 1) / 2;
}

int main() {
	scanf("%d", &N);
	int cnt = 0;
	memset(F, 0x3f, sizeof F);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
		if (A[i]) {
			Pos[++cnt] = i;
			F[cnt][i][0] = F[cnt - 1][Pos[cnt - 1]][0] + cal(i - Pos[cnt - 1] - 1);
		}
	}
	int total = N * (N - 1) / 2 - cnt * (cnt - 1) / 2 - (N - cnt) * cnt;
	F[0][0][0] = 0;
	for (int i = 1; i <= cnt; ++i) {
		for (int k = i - 1; k < N + i - cnt; ++k) {
			for (int t = 0; t <= N * (N - 1) / 2; ++t) {
				if (F[i - 1][k][t] == 0x3f3f3f3f) continue;
				for (int j = k + 1; j <= N + i - cnt; ++j) {
					F[i][j][t + abs(Pos[i] - j)] = min(F[i][j][t + abs(Pos[i] - j)], F[i - 1][k][t] + cal(j - k - 1));
				}
			}
		}
	}
	int ans = total;
	for (int i = 0; i <= N * (N - 1) / 2; ++i) {
		for (int j = cnt; j <= N; ++j) {
			ans = min(ans, F[cnt][j][i] + cal(N - j));
		}
		printf("%d ", total - ans);
	}
	return 0;
}
