/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-07 00:14:49
 * Url: https://codeforces.com/contest/1405/problem/E
 * O(N*log^2(N))
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, M, A[MAXN];
vector<pair<int, int>> v[MAXN];
int B[MAXN], Ans[MAXN];
int F[MAXN];
int Sum[MAXN];

int lowbit(int x) {
	return x & -x;
}

void add(int pos, int val) {
	for (; pos <= N; pos += lowbit(pos)) Sum[pos] += val;
}

int query(int pos) {
	int val = 0;
	for (; pos; pos -= lowbit(pos)) val += Sum[pos];
	return val;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		A[i] = i - A[i];
	}
	for (int i = 1, l, r; i <= M; ++i) {
		cin >> l >> r;
		v[N - r].push_back(make_pair(l + 1, i));
	}
	for (int i = 1; i <= N; ++i) {
		if (A[i] >= 0) {
			int l = 1, r = i, pos = 0;
			while (l <= r) {
				int m = (l + r) >> 1;
				if (query(m) >= A[i]) {
					l = m + 1;
					pos = m;
				} else r = m - 1;
			}
			if (pos) {
				add(1, 1);
				add(pos + 1, - 1);
			}
		}	
		for (auto u : v[i]) Ans[u.second] = query(u.first);
	}
	for (int i = 1; i <= M; ++i) cout << Ans[i] << endl;
	return 0;
}