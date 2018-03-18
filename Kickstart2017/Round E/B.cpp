#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <bitset>
#include <sstream>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <climits>
#include <ctype.h>
using namespace std;

#define PI acos(-1.0)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define fi first
#define se second

#define eps 1e-8
#define mod 1000000007

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;

#define MAXN 5010
int n;
int l[MAXN];
vector<pii> foo;
vector<int> helper;

int count(ll upper) {
    int left = 0, right = foo.size() - 1;
    while (left < right) {
        int mid = right - (right - left) / 2;
        if (foo[mid].first <= upper) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    return helper[left];
}

int query(ll left, ll right) {
    if (left > right) return 0;
    return count(right) - count(left - 1);
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        foo.clear();
        helper.clear();
        cin >> n;
        for (int j = 0; j < n; ++j) {
            scanf("%d", l + j);
        }
        sort(l, l + n);
        foo.push_back({0, 0});
        for (int j = 0; j < n; ++j) {
            if (j == 0 || l[j] != l[j - 1]) {
                foo.push_back({l[j], 1});
            } else {
                foo.back().second++;
            }
        }

        int sum = 0;
        for (int j = 0; j < foo.size(); ++j) {
            sum += foo[j].second;
            helper.pb(sum);
        }

        ll res = 0;
        for (int j = 1; j < foo.size(); ++j) {
            ll num = foo[j].second;
            ll tmp;
            if (num >= 3) {
                tmp = num * (num - 1) * (num - 2) / 6;
                // {a, a, a, c | a < c < 3 * a}
                res += tmp * query(foo[j].first + 1, 3LL * foo[j].first - 1);
                // {b, a, a, a | b < a}
                res += tmp * query(1, foo[j].first - 1);
            }
            if (num >= 2) {
                // {b, a, a, c | b < c < 2 * a + b}
                tmp = num * (num - 1) / 2;
                for (int k = 1; k < foo.size(); ++k) {
                    if (k == j) continue;
                    ll left = foo[k].first + 1, right = 2LL * foo[j].first + foo[k].first - 1;
                    res += tmp * foo[k].second * (query(left, right) - (left <= foo[j].first && foo[j].first <= right ? foo[j].second : 0));
                }
            }
        }

        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}