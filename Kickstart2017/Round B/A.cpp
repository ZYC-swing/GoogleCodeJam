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

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

ll myPow(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) {
            res *= base;
            res %= mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int j = 0; j < n; ++j) {
            cin >> nums[j];
        }
        ll res = 0;
        for (int p = 0; p < n - 1; ++p) {
            for (int q = p + 1; q < n; ++q) {
                res += (nums[q] - nums[p]) * myPow(2, q - p - 1);
                res %= mod;
            }
        }
        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}