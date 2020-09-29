#include <bits/stdc++.h>

const int MAXN = 80 + 5;

int N, cnt, B[MAXN];
struct Queue {
	int A[MAXN], qh, qt;
	Queue() {
		qh = 0, qt = 1;
	}
	void push(int x) {
		A[qt++] = x;
	}
} Que[MAXN][MAXN];

int main() {
	scanf("%d", &N);
	for (int i = 1, x; i <= N; ++i) {
		scanf("%d", &x);
		if (x) B[++cnt] = i;
	}
	for (int i = 1; i < B[2]; ++i) {
		Que[1][abs(i - B[1])].push(i);
	}
	for (int i = 2; i <= N * (N - 1) / 2; ++i) {
		for (int j = i; j <= N; ++j) {
			for (int k = i - 1; k <= N; ++k) {
				
			}
		}
	}
	return 0;
}