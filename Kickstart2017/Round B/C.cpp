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

int m, n;
map<vector<int>, int> helper;
int dp[101][101];
char matrix[101][101];

int dfs(int x, int y, int remain) {
    if (remain == 0) return 0;
    if (m - x < remain || x >= m || y < 0 || y >= n || matrix[x][y] == '.') return INT_MIN;
    if (helper.find({x, y, remain}) != helper.end()) return helper[{x, y, remain}];
    int res = 0;
    for (int h = 1; h <= dp[x][y]; ++h) {
        for (int col = y - h + 1; col <= y + h - 1; ++col) {
            res = max(res, h * h + dfs(x + h, col, remain - 1));
        }
    }
    return helper[{x, y, remain}] = (res == 0 ? INT_MIN : res);
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int k;
        cin >> m >> n >> k;
        for (int p = 0; p < m; ++p) {
            for (int q = 0; q < n; ++q) {
                cin >> matrix[p][q];
            }
        }
        memset(dp, 0, sizeof(dp));
        helper.clear();
        for (int row = m - 1; row >= 0; --row) {
            for (int col = 0; col < n; ++col) {
                if (matrix[row][col] == '#') {
                    if (row < m - 1 && col > 0 && col < n - 1) {
                        dp[row][col] = min(min(dp[row + 1][col - 1], dp[row + 1][col]), dp[row + 1][col + 1]);
                    }
                    ++dp[row][col];
                }
            }
        }

        int res = 0;
        for (int row = 0; row <= m - k; ++row) {
            for (int col = 0; col < n; ++col) {
                res = max(res, dfs(row, col, k));
            }
        }

        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}