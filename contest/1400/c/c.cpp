/* Code Information
 * Author: Skqliao
 * Time: 2020-08-25 23:48:40
 * Url: https://codeforces.com/contest/1400/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

int x;
string S, s;
bool flag;

bool isZero(int p) {
	bool flag = 1;
	if (p - x >= 0) flag &= (s[p - x] == '0');
	if (p + x < S.size()) flag &= (s[p + x] == '0');
	return flag;
}

bool isOne(int p) {
	bool flag = 0;
	if (p - x >= 0) flag |= (s[p - x] == '1');
	if (p + x < S.size()) flag |= (s[p + x] == '1');
	return flag;
}

bool check(int p) {
	return S[p] == '0' ? isZero(p) : isOne(p);
}

void update(int p, char c) {
	if (p >= 0 && p < S.size()) s[p] = c;
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> S >> x;
		s = S;
		flag = 1;
		for (size_t i = 0; i < S.size(); ++i) s[i] = '1';
		for (size_t i = 0; i < S.size(); ++i) {
			if (S[i] == '1') continue;
			update(i + x, '0');
			update(i - x, '0');
		}
		for (int i = 0; i < S.size(); ++i) flag &= check(i);
		if (!flag) puts("-1");
		else cout << s << endl;
	}
	return 0;
}
