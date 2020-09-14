/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-06 22:35:55
 * Url: https://codeforces.com/contest/1405/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100 + 5;

int T, N;
int A[MAXN], B[MAXN];

int main() {
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i = 1; i <= N; ++i) cin >> A[i];
		for (int i = N; i >= 1; --i) cout << A[i] << " ";
		cout << endl;
	}
	return 0;
}
