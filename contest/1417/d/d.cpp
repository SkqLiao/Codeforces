/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-27 23:31:45
 * Url: https://codeforces.com/contest/1417/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;

int T, N, A[MAXN];
struct Pair {
	int x, y, z;
};
vector<Pair> V;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
		int sum = 0;
		for (int i = 1; i <= N; ++i) sum += A[i];
		if (sum % N) {
			puts("-1");
			continue;
		}
		sum /= N;
		V.clear();
		for (int i = 2; i <= N; ++i) {
			if (A[i] % i) {
				V.push_back({1, i, i - A[i] % i});
				A[i] += i - A[i] % i;
			}
			V.push_back({i, 1, A[i] / i});
		}
		for (int i = 2; i <= N; ++i) {
			V.push_back({1, i, sum});
		}
		printf("%d\n", (int)V.size());
		for (auto u : V) printf("%d %d %d\n", u.x, u.y, u.z);
	}
	return 0;
}