/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-04 23:50:14
 * Url: 
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200 + 5;

int N, K;
string s, t;
int f[MAXN][MAXN][MAXN];
bool b[MAXN][MAXN][MAXN];

int main() {
	cin >> N >> K >> s >> t;
	s = "0" + s;
	if (t[0] == t[1]) {
		int num = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			if (s[i] == t[0]) ++num;
		}
		num = min(num + K, N);
		cout << num * (num - 1) / 2 << endl;
	} else {
		b[0][0][0] = 1;
		for (int i = 1; i <= N; ++i) {
			for (int j = 0; j <= min(i, K); ++j) {
				for (int k = 0; k <= i; ++k) {
					if (s[i] == t[1] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k] + k);
						b[i][j][k] = 1;
					}
					if (s[i] != t[1] && b[i - 1][j - 1][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + k);
						b[i][j][k] = 1;
					}
					if (s[i] != t[1] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
						b[i][j][k] = 1;
					}
					if (s[i] == t[0] && b[i - 1][j][k - 1]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1]);
						b[i][j][k] = 1;
					}
					if (s[i] != t[0] && b[i - 1][j - 1][k - 1]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1]);
						b[i][j][k] = 1;
					}
					if (s[i] != t[0] && b[i - 1][j][k]) {
						f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
						b[i][j][k] = 1;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i <= K; ++i) {
			for (int j = 0; j <= N; ++j) {
				ans = max(ans, f[N][i][j]);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
