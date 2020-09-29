/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-28 17:53:08
 * Url: https://codeforces.com/contest/1417/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;
const int MAXM = 35;

int N, A[MAXN];
vector<vector<int>> V[MAXM];
vector<int> v[2];
int Sum[MAXN], Sum2[MAXN];

void solve() {
	int ans = 0;
	long long res = 0;
    for (int p = 30; p >= 0; --p) {
		long long num1 = 0, num2 = 0;
		for (auto u : V[p]) {
            Sum[u.size()] = Sum2[u.size()] = 0;
            for (int i = u.size() - 1; i >= 0; --i) {
                Sum[i] = Sum[i + 1] + !(u[i] & (1 << p));
				Sum2[i] = Sum2[i + 1] + (bool)(u[i] & (1 << p));
            }
            for (int i = 0; i < u.size(); ++i) {
				if (u[i] & (1 << p)) num1 += Sum[i];
				else num2 += Sum2[i];
            }
			v[0].clear(), v[1].clear();
            for (auto x : u) {
                v[!(x & (1 << p))].push_back(x);
            }
			if (p == 0) continue;
			if (!v[0].empty()) V[p - 1].push_back(v[0]);
            if (!v[1].empty()) V[p - 1].push_back(v[1]);
        }
		res += min(num1, num2);
		if (num1 > num2) ans |= (1 << p);
    }
	printf("%lld %d\n", res, ans);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
    for (int i = 1; i <= N; ++i) v[0].push_back(A[i]);
    V[30].push_back(v[0]);
    solve();
    return 0;
}
