// problem: CF1420E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T &x, T y) {
    x = (y > x ? y : x);
}
template<typename T> inline void ckmin(T &x, T y) {
    x = (y < x ? y : x);
}

const int MAXN = 80, MAXOP = MAXN * (MAXN - 1) / 2;
const int INF = 0x3f3f3f3f;
int n, a[MAXN + 5], cnt[2], pos[MAXN + 5];
int total, max_op;
int dp[MAXOP + 5][MAXN + 5][MAXN + 5];
struct Queue {
    int a[MAXN + 5];
    int ql, qr;
    int size() {
        return qr - ql + 1;
    }
    bool empty() {
        return ql > qr;
    }
    int front() {
        return a[ql];
    }
    int back() {
        return a[qr];
    }
    int back2() {
        return a[qr - 1];
    }
    void push_back(int e) {
        a[++qr] = e;
    }
    void pop_back() {
        --qr;
    }
    void init() {
        ql = 1;
        qr = 0;
    }
} que[MAXOP + 5][MAXN + 5];

int calc(int len) {
    return len * (len - 1) / 2;
}
int calc2(int len) {
    return len * (len - 1);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        if (a[i] == 1) {
            pos[cnt[1]] = i;
        }
    }
    total = calc(cnt[0]);
    max_op = calc(n);
    if (!cnt[1]) {
        for (int i = 0; i <= max_op; ++i) cout << 0 << " "; cout << endl;
        return 0;
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int j = 0; j <= max_op; ++j) {
        for (int k = 1; k <= cnt[1]; ++k) {
            que[j][k].init();
        }
    }
    for (int i = 1; i <= n; ++i) {
#define Q que[abs(pos[1] - i)][1]
#define F dp[abs(pos[1] - i)][1]
#define Y(p) (F[(p)] + (p) * (p) + 3 * (p))

        F[i] = calc2(i - 1);
        while (Q.size() >= 2 && (Y(Q.back()) - Y(Q.back2())) * (i - Q.back()) > (Y(i) - Y(Q.back())) * (Q.back() - Q.back2()))
            Q.pop_back();
        Q.push_back(i);

#undef Q
#undef F
#undef Y
    }
    for (int j = 0; j <= max_op; ++j) {
        for (int k = 2; k <= cnt[1]; ++k) {
            for (int i = k; i <= n - (cnt[1] - k); ++i) {
                if (j < abs(pos[k] - i)) continue;
                int last_j = j - abs(pos[k] - i);
#define Q que[last_j][k - 1]
#define F dp[last_j][k - 1]
#define Y(p) (F[(p)] + (p) * (p) + 3 * (p))
                if (Q.empty()) continue;
                if(Q.front() >= i) continue;
                int l = Q.ql;
                int r = Q.qr;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (Q.a[mid] < i) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                l = Q.ql;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    int p1 = Q.a[mid], p2 = Q.a[mid + 1];
                    if (Y(p2) - Y(p1) > 2 * i * (p2 - p1)) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                ckmin(dp[j][k][i], F[Q.a[l]] + calc2(i - Q.a[l] - 1));
#undef Q
#undef F

#define Q que[j][k]
#define F dp[j][k]
                while (Q.size() >= 2 && (Y(Q.back()) - Y(Q.back2())) * (i - Q.back()) > (Y(i) - Y(Q.back())) * (Q.back() - Q.back2()))
                    Q.pop_back();
                Q.push_back(i);

#undef Q
#undef F
#undef Y
            }
        }
    }
    int res = total;
    for (int j = 0; j <= max_op; ++j) {
        for (int i = cnt[1]; i <= n; ++i) if (dp[j][cnt[1]][i] != INF) {
                ckmin(res, (dp[j][cnt[1]][i] + calc2(n - i)) / 2);
            }
        cout << total - res << " ";
    }
    cout << endl;
    return 0;
}