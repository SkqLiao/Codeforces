/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:27:56
 * Url: 
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int t, n, k;
int x[MAXN], y[MAXN];
int r[MAXN], num[MAXN];
int id[MAXN], ans[MAXN], mx[MAXN];

int get(int a) {
	return upper_bound(x + 1, x + n + 1, a) - x - 1;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) cin >> x[i];
		for (int i = 1; i <= n; ++i) cin >> y[i];
		sort(x + 1, x + n + 1);
		memset(num, 0, sizeof num);
		for (int i = 1; i <= n; ++i) {
			if (x[i] == x[i - 1]) id[i] = id[i - 1];
			else id[i] = id[i - 1] + 1;
			++num[id[i]];
		}
		n = unique(x + 1, x + n + 1) - x - 1;
		for (int i = 1; i <= n; ++i) num[i] += num[i - 1];
		for (int i = 1; i <= n; ++i) {
			ans[i] = num[r[i] = get(x[i] + k)] - num[i - 1];
		}
		mx[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			mx[i] = max(mx[i + 1], ans[i]);
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			res = max(res, ans[i] + mx[r[i] + 1]);
		}
		cout << res << endl;
	}
	return 0;
}
