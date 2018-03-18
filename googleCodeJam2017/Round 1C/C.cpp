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
#define PI acos(-1.0)
#define eps 1e-8

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

double myPow(double base, int exp) {
    double res = 1.0;
    while (exp) {
        if (exp & 1) {
            res *= base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/C-small-1-attempt0.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/C-small-1-attempt0.out", "w", stdout);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, k;
        cin >> n >> k;
        double u;
        cin >> u;
        vector<double> p(n);
        for (int j = 0; j < n; ++j) cin >> p[j];
        sort(begin(p), end(p));
        int j;
        double sum = 0.0;
        for (j = 0; j < n; ++j) {
            if (sum + u < j * p[j]) break;
            sum += p[j];
        }
        double tmp = (sum + u) / j;
        double res = myPow(tmp, j);
        for (; j < n; ++j) {
            res *= p[j];
        }
        printf("Case #%d: %.8lf\n", i, res);
    }

    return 0;
}