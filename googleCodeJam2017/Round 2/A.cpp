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

// return {gcd(a, b), x, y}, where a * x + b * y == gcd(a, b)
vector<int> extendGcd(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};
    } else {
        vector<int> tmp = extendGcd(b, a % b);
        return {tmp[0], tmp[2], tmp[1] - (a / b) * tmp[2]};
    }
}

ll moMul(ll a, ll b) {
    return ((a % mod) * (b % mod)) % mod;
}

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

int n, p;


int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/A-large.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/A-large.out", "w", stdout);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> p;
        vector<int> remain(p, 0);
        for (int j = 0; j < n; ++j) {
            int g;
            cin >> g;
            ++remain[g % p];
        }
        int res = 0;
        if (p == 2) {
            res = remain[0] + (remain[1] + 1) / 2;
        } else if (p == 3) {
            res = remain[0];
            int tmp = min(remain[1], remain[2]);
            res += tmp;
            remain[1] -= tmp, remain[2] -= tmp;
            if (remain[1]) {
                res += (remain[1] + 2) / 3;
            } else {
                res += (remain[2] + 2) / 3;
            }
        } else {// p == 4
            res = remain[0] + (remain[2] + 1) / 2;
            int tmp = min(remain[1], remain[3]);
            res += tmp;
            remain[1] -= tmp, remain[3] -= tmp;
            if (remain[1]) {
                res += (remain[1] + 3) / 4;
            } else {
                res += (remain[2] + 3) / 4;
            }
        }
        cout << "Case #" << i << ": " << res << endl;
//        printf("Case #%d: %.8lf\n", i, PI * res);
    }

    return 0;
}