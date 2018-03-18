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
#define MAXN 100010

int n, k, c, d, e1, e2, f, x, y, r, s;
int a[MAXN], b[MAXN];
ll prea[MAXN], preb[MAXN];
vector<ll> foo;

int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/B-small-attempt1.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/B-small-attempt1.out", "w", stdout);
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cin >> n >> k >> a[1] >> b[1] >> c >> d >> e1 >> e2 >> f;
        x = a[1], y = b[1], r = 0, s = 0;
        for (int j = 2; j <= n; ++j) {
            int xx = (c * x + d * y + e1) % f;
            int yy = (d * x + c * y + e2) % f;
            int rr = (c * r + d * s + e1) % 2;
            int ss = (d * r + c * s + e2) % 2;
            x = xx, y = yy, r = rr, s = ss;
            a[j] = (r % 2 == 0 ? 1 : -1) * x;
            b[j] = (s % 2 == 0 ? 1 : -1) * y;
        }
        memset(prea, 0, sizeof(prea));
        memset(preb, 0, sizeof(preb));
        for (int j = 1; j <= n; ++j) {
            prea[j] = prea[j - 1] + a[j];
            preb[j] = preb[j - 1] + b[j];
        }

        foo.clear();
        for (int r1 = 1; r1 <= n; ++r1) {
            for (int c1 = 1; c1 <= n; ++c1) {
                for (int r2 = r1; r2 <= n; ++r2) {
                    for (int c2 = c1; c2 <= n; ++c2) {
                        ll tmp = (prea[r2] - prea[r1 - 1]) * (preb[c2] - preb[c1 - 1]);
                        foo.pb(tmp);
                    }
                }
            }
        }

        nth_element(foo.begin(), foo.begin() + k - 1, foo.end(), greater<ll>());

        cout << "Case #" << i << ": " << foo[k - 1] << endl;
    }

    return 0;
}