#include <bits/stdc++.h>

const int MAXN = 1e6 + 5;

char s[MAXN], t[MAXN];
int Pi[MAXN];

void build(char *s) {
    int n = strlen(s);
    for (int i = 1; i < n; ++i) {
        int j = Pi[i - 1];
        while (j && s[j] != s[i]) j = Pi[j - 1];
        if (s[j] == s[i]) ++j;
        Pi[i] = j;
    }
}

void match(char *t) {
    int m = strlen(t), u = 0;
    for (int i = 0; i < m; ++i) {
        while (s[u] != t[i]) u = Pi[u - 1];
        if (++u == n) v.push_back();
    }
}

int main() {
    scanf("%s%s", s, t);
    build(s);
    match(t);
    return 0;
}