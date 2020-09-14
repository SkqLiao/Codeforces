/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-08 23:37:18
 * Url: https://codeforces.com/contest/1407/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, A[MAXN];
int F[MAXN];
stack<int> S;
int Lx[MAXN], Ln[MAXN], Rx[MAXN], Rn[MAXN];

bool check(int x) { return 1 <= x && x <= N; }

bool cmp(int x, int y, bool c) {
	return c ? x >= y : x <= y;
}

void get(int inc, int B[], bool c) {
	while (!S.empty()) S.pop();
	int cur = inc == -1 ? N : 1;
	S.push(cur);
	cur += inc;
	while (check(cur)) {
		if (!S.empty() && cmp(A[cur], A[S.top()], c)) {
			B[S.top()] = cur; S.pop();
		} else {
			S.push(cur);
			cur += inc;
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	get(1, Rx, 1); get(1, Rn, 0);
	get(-1, Lx, 1); get(-1, Ln, 0);
	memset(F, 0x3f, sizeof F);
	F[1] = 0;
	for (int i = 1; i <= N; ++i) {
		if (Ln[i])	F[i] = min(F[i], F[Ln[i]] + 1);
		if (Lx[i])	F[i] = min(F[i], F[Lx[i]] + 1);
		if (Rx[i])	F[Rx[i]] = min(F[Rx[i]], F[i] + 1);
		if (Rn[i])	F[Rn[i]] = min(F[Rn[i]], F[i] + 1);
	}
	cout << F[N] << endl;
	return 0;
}
