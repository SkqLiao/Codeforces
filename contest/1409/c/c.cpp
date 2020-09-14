/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:47:41
 * Url: 
**/

#include <bits/stdc++.h>

using namespace std;

int T, n, x, y, z;

int get(int a) {
	if (z / a + 1 > n) return INT_MAX;
	int mn = x - x / a * a;
	if (!mn) mn += a;
	int num = (y - mn) / a + 1;
	if (num >= n) return y;
	else return y + (n - num) * a;
}

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> x >> y;
		z = y - x;
		int ans = INT_MAX, dv;
		for (int i = 1; i <= sqrt(z) + 1; ++i) {
			if (z % i == 0) {
				int tmp = get(i);
				if (ans > tmp) {
					ans = tmp;
					dv = i;
				}
				//cout << i << " : " << tmp << endl;
				tmp = get(z / i);
				if (ans > tmp) {
					ans = tmp;
					dv = z / i;
				}
				//cout << z / i << " : " << tmp << endl;
			}
		}
		for (int i = ans - dv * (n - 1); i <= ans; i += dv) cout << i << " ";
		cout << endl;
	}
	return 0;
}
