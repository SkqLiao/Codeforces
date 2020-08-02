/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 10:02:12
 * Url: https://codeforces.com/contest/1255/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;
const int Dicx[] = {0, 1, 0, -1};
const int Dicy[] = {1, 0, -1, 0};

int T, N, M, P;
string S[MAXN];
char D[MAXN][MAXN];

char getX(int x) {
	if (x < 26) return 'A' + x;
	else if (x < 52) return 'a' + x - 26;
	else return x - 52 + '0';
}

bool check(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M && !D[x][y];
}

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> M >> P;
		for (int i = 0; i < N; ++i) cin >> S[i];
		int total = 0;
		for (int i = 0; i < N; ++i) 
			for (int j = 0; j < M; ++j)
				total += S[i][j] == 'R';
		int num = total % P, cnt = total / P;
		int cx = 0, cy = 0, pos = 0, cur = 0, dir = 0, step = 0;
		memset(D, 0, sizeof D);
		while (step < N * M) {
			++step;
			if (S[cx][cy] == 'R' && cur == cnt + (pos < num)) pos += 1, cur = 0;
			cur += S[cx][cy] == 'R';
			D[cx][cy] = getX(pos);
			if (!check(cx + Dicx[dir], cy + Dicy[dir])) dir = (dir + 1) % 4;
			cx += Dicx[dir], cy += Dicy[dir];
		}
		for (int i = 0; i < N; ++i) cout << D[i] << "\n";
	}
	return 0;
}
