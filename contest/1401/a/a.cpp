/* Code Information
 * Author: Skqliao
 * Time: 2020-08-22 19:19:00
 * Url: https://codeforces.com/contest/1401/problem/A
**/

#include <bits/stdc++.h>

using namespace std;

int T, N, M;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        if (M > N) printf("%d\n", M - N);
        else printf("%d\n", (N - M) & 1);
    }
	return 0;
}
