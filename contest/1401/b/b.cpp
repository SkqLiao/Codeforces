/* Code Information
 * Author: Skqliao
 * Time: 2020-08-22 19:31:21
 * Url: https://codeforces.com/contest/1401/problem/B
**/

#include <bits/stdc++.h>

using namespace std;

int T;
int A[3], B[3];

int main() {
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 3; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < 3; ++i) scanf("%d", &B[i]);
        B[2] -= min(B[2], A[0]);
        int x = min(A[2], B[2]);
        A[2] -= x, B[2] -= x;
        printf("%d\n", 2 * (min(A[2], B[1]) - min(B[2], A[1])));
    }
	return 0;
}
