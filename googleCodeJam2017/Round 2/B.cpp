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

int n, c, m;

pii solve(vector<vector<int>>& tickets) {
    pii conflict, foo;
    conflict = foo = {0, 0};
    int res = 0;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (tickets[0][i] == 0 || tickets[1][i] == 0) {
            foo.first += tickets[0][i];
            foo.second += tickets[1][i];
        } else {
            if (conflict.first >= tickets[1][i]) {
                if (conflict.second >= tickets[0][i]) {
                    conflict.first -= tickets[1][i];
                    conflict.second -= tickets[0][i];
                    res += tickets[0][i] + tickets[1][i];
                } else {
                    res += conflict.second + tickets[1][i];
                    foo.first += conflict.first - conflict.second + tickets[0][i] - tickets[1][i];
                    conflict.first = conflict.second = 0;
                    flag = false;
                }
            } else {
                if (conflict.second >= tickets[0][i]) {
                    res += conflict.first + tickets[0][i];
                    foo.second += conflict.second - conflict.first + tickets[1][i] - tickets[0][i];
                    conflict.first = conflict.second = 0;
                    flag = false;
                } else {
                    res += conflict.first + conflict.second;
                    int tmp = conflict.first;
                    conflict.first = tickets[0][i] - conflict.second;
                    conflict.second = tickets[1][i] - tmp;
                    flag = i ? false : true;
                }
            }
        }
    }

    int prom = 0;
    if (conflict.first >= foo.second) {
        if (conflict.second >= foo.first) {
            res += foo.first + foo.second;
            conflict.first -= foo.second;
            conflict.second -= foo.first;
            if (flag) {
                res += conflict.first + conflict.second;
            } else {
                res += max(conflict.first, conflict.second);
                prom = min(conflict.first, conflict.second);
            }
        } else {
            res += conflict.first + foo.first;
        }
    } else {
        if (conflict.second >= foo.first) {
            res += conflict.second + foo.second;
        } else {
            res += conflict.first + conflict.second;
            foo.first -= conflict.second;
            foo.second -= conflict.first;
            res += max(foo.first, foo.second);
        }
    }
    return {res, prom};
}

int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/B-small-attempt1.in", "r", stdin);
//    freopen("/Users/Swing/Documents/code/googleCodeJam/B-small-attempt1.out", "w", stdout);
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> c >> m;
        vector<vector<int>> tickets(c, vector<int>(n, 0));
        for (int j = 0; j < m; ++j) {
            int label, index;
            cin >> label >> index;
            ++tickets[index - 1][label - 1];
        }
        pii res = solve(tickets);
        cout << "Case #" << i << ": " << res.first << " " << res.second << endl;
//        printf("Case #%d: %.8lf\n", i, PI * res);
    }

    return 0;
}