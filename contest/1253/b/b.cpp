/* Code Information
 * Author: Skqliao
 * Time: 2020-07-26 09:59:19
**/

#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int N, A[MAXN];
std::set<int> S, T;
std::vector<int> v;

void Solve() {
	int total = 0, cnt = 0, lst = 0;
	for (int i = 1; i <= N; ++i) {
		if (A[i] > 0) {
			if (T.find(A[i]) != T.end()) {
				puts("-1");
				return ;
			}
			S.insert(A[i]);
			T.insert(A[i]);
			total += A[i];
		} else {
			A[i] = -A[i];
			if (S.find(A[i]) == S.end()) {
				puts("-1");
				return ;
			}
			S.erase(A[i]);
			total -= A[i];
			if (total == 0) {
				++cnt;
				v.push_back(i - lst);
				lst = i;
				T.clear();
			}
		}
	}
	if (total != 0) {
		puts("-1");
		return ;
	}
	printf("%d\n", cnt);
	for (auto i : v) 
		printf("%d ", i);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]);
	Solve();
	return 0;
}
