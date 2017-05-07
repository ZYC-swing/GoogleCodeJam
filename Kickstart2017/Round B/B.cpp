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

#define mod 1000000007
#define PI acos(-1.0)
#define eps 1e-8

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

#define MAXN 10000
#define BOUND 1000
int n;
struct Point {
    double x;
    double y;
    double w;
} points[MAXN + 1];

double calu(Point center) {
    double res = 0.0;
    for (int i = 0; i < n; ++i) {
        res += max(fabs(center.x - points[i].x), fabs(center.y - points[i].y)) * points[i].w;
    }
    return res;
}

double solve1(double x) {
    double l = -BOUND, r = BOUND;
    double res = 1e11;
    while (r - l > eps) {
        double tmp = (r - l) / 3;
        double mid1 = l + tmp, mid2 = r - tmp;
        double res1 = calu({x, mid1, 0}), res2 = calu({x, mid2, 0});
        if (res1 > res2) {
            l = mid1;
            res = min(res, res2);
        } else {
            r = mid2;
            res = min(res, res1);
        }
    }
    return res;
}

double solve() {
    double l = -BOUND, r = BOUND;
    double res = 1e11;
    while (r - l > eps) {
        double tmp = (r - l) / 3;
        double mid1 = l + tmp, mid2 = r - tmp;
        double res1 = solve1(mid1), res2 = solve1(mid2);
        if (res1 > res2) {
            l = mid1;
            res = min(res, res2);
        } else {
            r = mid2;
            res = min(res, res1);
        }
    }
    return res;
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n;
        for (int j = 0; j < n; ++j) {
            cin >> points[j].x >> points[j].y >> points[j].w;
        }

        printf("Case #%d: %.8lf\n", i, solve());
    }

    return 0;
}