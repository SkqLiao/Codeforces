/* Code Information
 * Author: Skqliao
 * Time: 2020-08-28 11:36:46
 * Url: https://codeforces.com/contest/1400/problem/E
**/
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 5000 + 5;
const int MAXM = 15;
 
int N, A[MAXN];
int Mn[MAXN][MAXN], P[MAXN][MAXM];
int Pow[MAXM], Log[MAXN];
 
void initST() {
	Pow[0] = 1;
	for (int i = 1; i < MAXM; ++i) Pow[i] = Pow[i - 1] * 2;
	for (int i = 2; i <= N; ++i) Log[i] = Log[i / 2] + 1;
	for (int i = 1; i <= N; ++i) Mn[i][0] = A[i], P[i][0] = i;
	for (int i = 1; i <= Log[N]; ++i) {
    	for (int j = 1; j + Pow[i] - 1 <= N; ++j) {
			Mn[j][i] = min(Mn[j][i - 1], Mn[j + Pow[i - 1]][i - 1]);
			if (Mn[j][i - 1] <= Mn[j + Pow[i - 1]][i - 1]) {
				P[j][i] = P[j][i - 1];
			} else {
				P[j][i] = P[j + Pow[i - 1]][i - 1];
			}
        }
    }
}
 
int queryMinVal(int l, int r) {
	int k = Log[r - l + 1];
	return min(Mn[l][k], Mn[r - Pow[k] + 1][k]);
}
 
int queryMinPos(int l, int r) {
	int k = Log[r - l + 1];
	return Mn[l][k] <= Mn[r - Pow[k] + 1][k] ? P[l][k] : P[r - Pow[k] + 1][k];
}
 
int solve(int l, int r, int val) {
	if (l > r) return 0;
	if (l == r) return A[l] != val;
	int mn = queryMinVal(l, r), p = queryMinPos(l, r);
	return min(mn - val + solve(l, p - 1, mn) + solve(p + 1, r, mn), r - l + 1);
}
 
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
	initST();
	printf("%d\n", solve(1, N, 0));
	return 0;
}