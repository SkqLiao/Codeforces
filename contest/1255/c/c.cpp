/* Code Information
 * Author: Skqliao
 * Time: 2020-08-01 00:01:59
 * Url: https://codeforces.com/contest/1255/problem/C
**/

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair

const int MAXN = 1e5 + 5;

int N;
int Tms[MAXN], Ans[MAXN];
map<pair<int, int>, pair<int, int>> Map;

void add(int a, int b, int c) {
	pair<int, int> x = mp(min(a, b), max(a, b));
	if (Map.find(x) != Map.end()) Map[x] = mp(Map[x].first, c);
	else Map[x] = mp(c, 0);
}

int main() {
	scanf("%d", &N);
	for (int i = 1, a[3]; i <= N - 2; ++i) {
		for (int i = 0; i < 3; ++i) {
			scanf("%d", &a[i]);
			++Tms[a[i]];
		}
		sort(a, a + 3);
		for (int i = 0; i < 3; ++i) add(a[i], a[(i + 1) % 3], a[(i + 2) % 3]);
	}
	for (int i = 1; i <= N; ++i)
		if (Tms[i] == 1) Ans[1] = i;
	for (int i = 1; i <= N; ++i)
		if (Tms[i] == 2 && Map.find(mp(min(Ans[1], i), max(Ans[1], i))) != Map.end()) Ans[2] = i;
	Ans[3] = Map[mp(min(Ans[1], Ans[2]), max(Ans[1], Ans[2]))].first;
	for (int i = 4; i <= N; ++i) {
		pair<int, int> x = Map[mp(min(Ans[i - 2], Ans[i - 1]), max(Ans[i - 2], Ans[i - 1]))];
		if (x.first == Ans[i - 3]) Ans[i] = x.second;
		else Ans[i] = x.first;
	}	
	for (int i = 1; i <= N; ++i) printf("%d ", Ans[i]);
	return 0;
}