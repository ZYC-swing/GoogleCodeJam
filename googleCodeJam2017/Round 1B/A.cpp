#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define ull unsigned long long
#define mo 1000000007

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

#define N 1000

int d, n;
int k[N];
int speed[N];

double solve() {
    double res = 1.0 * d * speed[0] / (d - k[0]);
    for (int i = 1; i < n; ++i) {
        res = min(res, 1.0 * d * speed[i] / (d - k[i]));
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> d >> n;
        for (int j = 0; j < n; ++j) {
            cin >> k[j] >> speed[j];
        }
        printf("Case #%d: %.6lf\n", i, solve());
    }

    return 0;
}