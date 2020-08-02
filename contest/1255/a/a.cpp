/* Code Information
 * Author: Skqliao
 * Time: 2020-07-31 10:09:52
 * Url: https://codeforces.com/contest/1255/problem/A
**/

#include <bits/stdc++.h>

int T;
int A[] = {0, 1, 1, 2, 2};

int main() {
	int a, b;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &a, &b);
		int c = abs(a - b);
		printf("%d\n", c / 5 + A[c % 5]);
	}
	return 0;
}
