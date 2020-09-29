/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-24 17:34:23
 * Url: https://codeforces.com/contest/1418/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int T, x, y, z;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &x, &y, &z);
		int ans = INT_MAX;
		if (x > z) ans = min(ans, z - y);
		if (y > z) ans = min(ans, z - x);
		printf("%d\n", ans);
	}
	return 0;
}
