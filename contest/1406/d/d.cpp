/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-12 22:22:08
 * Url: https://codeforces.com/contest/1406/problem/D
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N, M;
long long A[MAXN], sum;

void change(int p, int x) {
	if (p > N) return ;
	if (A[p] > 0) sum -= A[p];
	A[p] += x;
	sum += max((long long)0, A[p]);
}

int main() {
	int l, r, x;
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> A[i];
	for (int i = N; i >= 1; --i) A[i] -= A[i - 1];
	for (int i = 2; i <= N; ++i) sum += max((long long)0, A[i]);
	cout << (long long)ceil((sum + A[1]) / 2.0) << endl;
	cin >> M;
	while (M--) {
		cin >> l >> r >> x;
		if (l == 1) A[1] += x;
		else change(l, x);
		change(r + 1, -x);
		cout << (long long)ceil((sum + A[1]) / 2.0) << endl;
	}
	return 0;
}
