/* Code Information
 * Author: Skqliao
 * Time: 2020-08-25 22:40:39
 * Url: https://codeforces.com/contest/1400/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

int T, P, F, Cs, Cw, S, W;

int main() {
	cin >> T;
	while (T--) {
		cin >> P >> F >> Cs >> Cw >> S >> W;
		if (S < W) {
			swap(S, W);
			swap(Cs, Cw);
		}
		int ans = 0;
		for (int i = 0; i <= Cw; ++i) {
			if (i * W > P) break;
			int total = i;
			int lw = Cw - i;
			total += min(Cs, (P - i * W) / S);
			int ls = Cs - min(Cs, (P - i * W) / S);
			total += min(lw, F / W);
			total += min((F - W * min(lw, F / W)) / S, ls);
			ans = max(ans, total);
		}
		cout << ans << endl;
	}
	return 0;
}
