/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 22:35:20
 * Url: https://codeforces.com/contest/1409/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int main() {
	int T, a, b;
	cin >> T;
	while (T--) {
		cin >> a >> b;
		cout << (abs(a - b) / 10 + (abs(a - b) % 10 != 0)) << endl;
	}
	return 0;
}
