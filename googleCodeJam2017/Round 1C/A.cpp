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

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, k;
        cin >> n >> k;
        vector<pii> cakes(n);
        for (int j = 0; j < n; ++j) {
            cin >> cakes[j].first >> cakes[j].second;
        }
        sort(begin(cakes), end(cakes));
        priority_queue<ll, vector<ll>, greater<ll>> qq;
        double res = 0;
        for (int j = 0; j < k; ++j) {
            qq.push(2L * cakes[j].first * cakes[j].second);
            res += 2.0 * cakes[j].first * cakes[j].second;
        }
        res += 1.0 * cakes[k - 1].first * cakes[k - 1].first;
        double tmp = res;
        for (int j = k; j < n; ++j) {
            tmp -= 1.0 * cakes[j - 1].first * cakes[j - 1].first;
            tmp += 1.0 * cakes[j].first * cakes[j].first + 2.0 * cakes[j].first * cakes[j].second;
            ll bar = qq.top();
            qq.pop();
            tmp -= 1.0 * bar;
            qq.push(2L * cakes[j].first * cakes[j].second);
            res = max(res, tmp);
        }
        printf("Case #%d: %.8lf\n", i, PI * res);
    }

    return 0;
}