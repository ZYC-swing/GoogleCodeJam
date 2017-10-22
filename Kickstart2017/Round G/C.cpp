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

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<int>> vvi;

struct Matrix {
    vvi data;
    int r, c;
    Matrix(int row, int col, bool identity = false) : r(row), c(col) {
        data.assign(row, vector<int>(col, 0));
        if (identity) {
            for (int i = 0; i < r; ++i) {
                data[i][i] = 1;
            }
        }
    }
    Matrix operator * (Matrix& other) {
        int m = r, n = c, p = other.c;
        Matrix res(m, p);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < p; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return res;
    }
};

// 扩展欧几里得算法 res[1] * a + res[2] * b = res[0] = gcd(a, b)
vector<int> extendGcd(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};
    } else {
        vector<int> tmp = extendGcd(b, a % b);
        return {tmp[0], tmp[2], tmp[1] - (a / b) * tmp[2]};
    }
}

// 矩阵快速幂
Matrix matrix_power(Matrix base, ll exp) {
    int n = base.r;
    Matrix res(n, n, true);
    while (exp) {
        if (exp & 1) {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

// 带模快速幂
ll power_mod(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 快速幂
ll power(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

// 求逆元
ll inv(ll a) {
    return power_mod(a, mod - 2);
}

#define MAXFAC 100010

ll fac[MAXFAC];

void initFac() {
    fac[0] = 1;
    for (int i = 1; i < MAXFAC; ++i) {
        fac[i] = i * fac[i - 1] % mod;
    }
}

ll Combine(ll a, ll b) {
    return (fac[a] * inv(fac[b]) % mod) * inv(fac[a - b]) % mod;
}

/******************************** template ********************************/
#define MAXN 50
#define MAXEXP 7
int n, m;
int g[MAXN][MAXN];

ll dp[MAXN][MAXN][MAXN][MAXN];

int st[MAXN][MAXEXP][MAXN][MAXEXP];

void init() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            st[i][0][j][0] = g[i][j];
        }
    }

    for (int col = 0; col < m; ++col) {
        for (int expr = 1; expr < MAXEXP; ++expr) {
            for (int row = 0; row <= n - (1 << expr); ++row) {
                st[row][expr][col][0] = min(st[row][expr - 1][col][0], st[row + (1 << (expr - 1))][expr - 1][col][0]);
            }
        }
    }

    for (int row = 0; row < n; ++row) {
        for (int expc = 1; expc < MAXEXP; ++expc) {
            for (int col = 0; col <= m - (1 << expc); ++col) {
                st[row][0][col][expc] = min(st[row][0][col][expc - 1], st[row][0][col + (1 << (expc - 1))][expc - 1]);
            }
        }
    }

    for (int expr = 1; expr < MAXEXP; ++expr) {
        for (int expc = 1; expc < MAXEXP; ++expc) {
            for (int row = 0; row <= n - (1 << expr); ++row) {
                for (int col = 0; col <= m - (1 << expc); ++col) {
                    st[row][expr][col][expc] = min(min(st[row][expr - 1][col][expc - 1], st[row][expr - 1][col + (1 << (expc - 1))][expc - 1]),
                                                   min(st[row + (1 << (expr - 1))][expr - 1][col][expc - 1], st[row + (1 << (expr - 1))][expr - 1][col + (1 << (expc - 1))][expc - 1]));
                }
            }
        }
    }
}

int rmq(int l, int r, int u, int d) {
    int expr, valr, expc, valc;
    expr = expc = 0, valr = valc = 1;
    int nrow = d - u + 1, ncol = r - l + 1;
    while (2 * valr < nrow) {
        valr <<= 1;
        ++expr;
    }
    while (2 * valc < ncol) {
        valc <<= 1;
        ++expc;
    }
    return min(min(st[u][expr][l][expc], st[u][expr][r - (1 << expc) + 1][expc]),
               min(st[d - (1 << expr) + 1][expr][l][expc], st[d - (1 << expr) + 1][expr][r - (1 << expc) + 1][expc]));
}

ll solve(int l, int r, int u, int d) {
    if (dp[l][r][u][d] != -1) return dp[l][r][u][d];
    if (l == r && u == d) return 0;
    int mini = rmq(l, r, u, d);
    ll res = 0;
    if (l < r) {
        for (int i = l; i < r; ++i) {
            res = max(res, solve(l, i, u, d) + solve(i + 1, r, u, d));
        }
    }
    if (u < d) {
        for (int i = u; i < d; ++i) {
            res = max(res, solve(l, r, u, i) + solve(l, r, i + 1, d));
        }
    }
    return dp[l][r][u][d] = res + mini;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> m;
        for (int p = 0; p < n; ++p) {
            for (int q = 0; q < m; ++q) {
                scanf("%d", &g[p][q]);
            }
        }
        init();
        cout << "Case #" << i << ": " << solve(0, m - 1, 0, n - 1) << endl;
    }

    return 0;
}