/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-09 13:57:53
 * Url: https://codeforces.com/contest/1407/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 5;

int N, A[MAXN], B[MAXN];

int get(int x, int y) {
    int a, b;
    cout << "? " << x << " " << y << endl;
    cout.flush();
    cin >> a;
    cout << "? " << y << " " << x << endl;
    cin >> b;
    if (a > b) swap(x, y), swap(a, b);
    A[y] = b, B[b] = 1;
    return x;
}

int main() {
    cin >> N;
    if (N == 1) {
        cout << "! 1" << endl; cout.flush();
        return 0;
    }
    int cur = get(1, 2);
    for (int i = 3; i <= N; ++i) cur = get(cur, i);
    for (int i = 1; i <= N; ++i) if (!B[i]) A[cur] = i;
    cout << "! ";
    for (int i = 1; i <= N; ++i) cout << A[i] << " ";
    cout << endl; cout.flush();
    return 0;
}
