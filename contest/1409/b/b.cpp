/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:38:02
 * Url: 
**/

#include <bits/stdc++.h>

using namespace std;

long long T, a, b, x, y, n;

long long get(long long a, long long b, long long x, long long y) {
	a -= n;
	if (a < x) {
		b -= (x - a);
		a = x;
	}
	b = max(b, y);
	return a * b;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> a >> b >> x >> y >> n;
		cout << min(get(a, b, x, y), get(b, a, y, x)) << endl;
	}
	return 0;
}
