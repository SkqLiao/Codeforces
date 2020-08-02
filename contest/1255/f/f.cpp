/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 13:53:16
 * Url: https://codeforces.com/contest/1255/problem/F
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000 + 5;

int N, P[MAXN];
long long D[MAXN];
vector<pair<long long, int>> v, f[2];

int main() {
	scanf("%d", &N);
	P[1] = 1, P[2] = 2;
	for (int i = 3, x; i <= N; ++i) {
		printf("2 1 %d %d\n", P[2], i); fflush(stdout);
		scanf("%d", &x);
		if (x == -1) P[2] = i;
	}
	for (int i = 2; i <= N; ++i) {
		if (i == P[2]) continue;
		printf("1 1 %d %d\n", P[2], i); fflush(stdout);
		scanf("%lld", &D[i]);
		v.push_back(make_pair(D[i], i));
	}
	sort(v.begin(), v.end());
	int p = v.back().second;
	for (int i = 2, x; i <= N; ++i) {
		if (i == p || i == P[2]) continue;
		printf("2 1 %d %d\n", p, i); fflush(stdout);
		scanf("%d", &x);
		f[x == -1].push_back(make_pair(D[i], i));
	}
	sort(f[0].begin(), f[0].end());
	sort(f[1].begin(), f[1].end());
	printf("0 %d %d ", P[1], P[2]);
	for (int i = 0; i < f[1].size(); ++i) printf("%d ", f[1][i].second);
	printf("%d ", p);
	for (int i = f[0].size() - 1; i >= 0; --i) printf("%d ", f[0][i].second);
	fflush(stdout);
	return 0;
}
