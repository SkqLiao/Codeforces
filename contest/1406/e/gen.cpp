#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000 + 5;

int N, M;
int Vis[MAXN];
int cnt;
char ch;
int x;

int main() {
    scanf("%d%d", &N, &M);
    printf("%d\n", N);
    cerr << N << endl;
    fflush(stdout);
    cnt = N;
    while (scanf("%c %d", &ch, &x)) {
        if (ch == 'A' || ch == 'B') {
            if (x == 1) {
                fprintf(stderr, "%c %d\n", ch, x);
                printf("%d\n", cnt);
                fprintf(stderr, "%d\n", cnt);
                fflush(stdout);
                continue;
            }
            int total = 0;
            for (int i = x; i <= N; i += x) {
                total += !Vis[i];
            }
            printf("%d\n", total);
            fprintf(stderr, "%d\n", total);
            if (total < 10) {
                for (int i = x; i <= N; i += x) {
                    if (!Vis[i]) fprintf(stderr, "%d ", i);
                }
                fprintf(stderr, "\n");
            }
            fflush(stdout);
        }
        if (ch == 'B') {
            for (int i = x; i <= N; i += x) {
                if (i != M) Vis[i] = 1;
            }
            cnt = 0;
            for (int i = 1; i <= N; ++i) cnt += !Vis[i];
        }
        if (ch == 'C') {
            cerr << M << " vs " << x << endl;
            break;
        }
    }
    return 0;
}