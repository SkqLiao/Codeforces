/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:06:31
 * Url: https://codeforces.com/contest/1409/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

long long t, x, y;
int len;
char a[20];
int s[20];

int main() {
	cin >> t;
	while (t--) {
		cin >> x >> y;
		sprintf(a, "%lld", x);
		len = strlen(a);
		s[0] = a[0] - '0';
		for (int i = 1; i < len; ++i) s[i] = s[i - 1] + a[i] - '0';
		if (s[len - 1] <= y) {
			cout << 0 << endl;
			continue;
		}
		bool flag = 0;
		for (int i = len - 2; i >= 1; --i) {
			if (a[i] == '9') continue;
			int cur = s[i - 1] + a[i] - '0' + 1;
			if (cur <= y) {
				a[i] += 1;
				for (int j = i + 1; j < len; ++j) a[j] = '0';
				flag = 1;
				break;
			}
		}
		if (!flag) {
			if (a[0] != '9' && a[0] + 1 - '0' <= y) {
				a[0]++;
				for (int i = 1; i < len; ++i) a[i] = '0';
			} else {
				a[0] = '1';
				for (int i = 1; i <= len; ++i) a[i] = '0';
				++len;
			}
		}
		long long z = 0;
		for (int i = 0; i < len; ++i) z = z * 10 + a[i] - '0';
		cout << z - x << endl;
	}
	return 0;
}
