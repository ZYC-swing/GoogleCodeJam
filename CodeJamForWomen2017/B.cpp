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

#define ll long long
#define ull unsigned long long
#define mo 1000000007

using namespace std;
typedef pair<int, int> pii;

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<double> p(2 * n);
        for (int j = 0; j < 2 * n; ++j) {
            cin >> p[j];
        }
        sort(begin(p), end(p));
        double res = 1.0;
        for (int l = 0, r = 2 * n - 1; l < r; ++l, --r) {
            res *= (1 - p[l] * p[r]);
        }

        printf("Case #%d: %.8f\n", i, res);
    }

    return 0;
}