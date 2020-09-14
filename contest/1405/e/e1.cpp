/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-09 20:24:06
 * Url: https://codeforces.com/contest/1405/problem/E
 * O(N*log(N))
**/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 5;

int N, M, A[MAXN];
vector<pair<int, int>> V[MAXN];
int Ans[MAXN];
int Sum[MAXN << 2];

void add(int rt, int l, int r, int p) {
    if (l == r) {
        ++Sum[rt];
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) add(rt << 1, l, m, p);
    else add(rt << 1 | 1,m + 1, r, p);
    Sum[rt] = Sum[rt << 1] + Sum[rt << 1 | 1];
}

int Bquery(int rt, int l, int r, int x) {
    if (l == r) return l;
    int m = (l + r) >> 1;
    if (Sum[rt << 1 | 1] >= x) return Bquery(rt << 1 | 1, m + 1, r, x);
    else return Bquery(rt << 1, l, m, x - Sum[rt << 1 | 1]);
}

int querySum(int rt, int l, int r, int a, int b) {
    if (a <= l && r <= b) return Sum[rt];
    int m = (l + r) >> 1, sum = 0;
    if (a <= m) sum += querySum(rt << 1, l, m, a, b);
    if (m < b) sum += querySum(rt << 1 | 1, m + 1, r, a, b);
    return sum;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        A[i] = i - A[i];
    }
    for (int i = 1, l, r; i <= M; ++i) {
        cin >> l >> r;
        V[N - r].push_back(make_pair(l + 1, i));
    }
    for (int i = 1; i <= N; ++i) {
        if (A[i] == 0) add(1, 1, N, i);
        else if (A[i] > 0 && Sum[1] >= A[i]) add(1, 1, N, Bquery(1, 1, N, A[i]));
        for (auto u : V[i]) Ans[u.second] = querySum(1, 1, N, u.first, i);
    }
    for (int i = 1; i <= M; ++i) cout << Ans[i] << endl;
    return 0;
}