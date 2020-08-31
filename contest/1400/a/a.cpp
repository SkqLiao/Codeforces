/* Code Information
 * Author: Skqliao
 * Time: 2020-08-25 22:35:24
 * Url: https://codeforces.com/contest/1400/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int T, N;
string S, ans;

int main() {
	cin >> T;
	while (T--) {
		cin >> N >> S;
		for (size_t i = 0; i < S.size(); i += 2) cout << S[i];
		cout << endl;
	}
	return 0;
}
