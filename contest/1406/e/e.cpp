/* Code Information
 * Author: little_skqliao
 * Time: 2020-09-13 12:53:11
 * Url: https://codeforces.com/contest/1406/problem/E
**/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N, P = 1;
vector<int> Pri;
bitset<MAXN> isnPri;

void getPrime() {
    for (int i = 2; i <= N; ++i) {
        if (!isnPri[i]) Pri.push_back(i);
        for (auto u : Pri) {
            int x = i * u;
            if (x > N) break;
            isnPri.set(x);
            if (i % u == 0) break;
        }
    }
}

int num;

int checkA(int x) {
    printf("A %d\n", x); fflush(stdout);
    scanf("%d", &num);
    return num;
}

int checkB(int x) {
	printf("B %d\n", x); fflush(stdout);
    scanf("%d", &num);
    return num;
}

int get(int x) {
    checkB(x);
	int ans = 1;
    for (int c = x; c * P <= N; c *= x) {
        if (!checkA(c)) break;
		ans *= x;
    }
	return ans;
}

int main() {
	scanf("%d", &N);
    if (N == 1) {
        puts("C 1");
        return 0;
    }
    getPrime();
    int r = -1;
    for (int i = 0; Pri[i] * Pri[i] <= N; ++i) P *= get(Pri[r = i]);
    int sz = sqrt(Pri.size() - r), num = checkA(1);
    for (int i = r + 1, cnt = 0; i < Pri.size(); ++i) {
        num -= checkB(Pri[i]);
        if (++cnt == sz || i == Pri.size() - 1) {
            int nnum = checkA(1);
            if (nnum != num) {
                for (int j = i - cnt + 1; j <= i; ++j) {
                    if (checkA(Pri[j])) {
                        P *= Pri[j];
                        break;
                    }
                }
                break;
            }
            num = nnum;
            cnt = 0;
        }
    }
    printf("C %d\n", P); fflush(stdout);
    return 0;
}
