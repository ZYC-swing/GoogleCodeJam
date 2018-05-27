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
#include <random>
#include <climits>
#include <cstdio>
#include <ctype.h>
#include <time.h>
using namespace std;

#define PI acos(-1.0)
#define EPS 1e-8
#define MOD 1000000007
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second
#define go(i, a, b) for(int i = a; i <= b; ++i)
#define gorev(i, a, b) for(int i = a; i >= b; --i)

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

template <class L, class R> ostream &operator <<(ostream &os, pair<L, R> P){
    return os << "(" << P.fi << "," << P.se << ")";
}
template <class T> ostream &operator <<(ostream &os, vector<T> V){
    os << "["; for (auto vv: V) os << vv << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}
template <class L, class R> ostream &operator <<(ostream &os, unordered_map<L, R> M){
    os << "["; for (auto pr: M) os << pr.fi << "->" << pr.se << ","; return os << "]";
}

mt19937_64 mt(time(0));

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

vector<int> extendGcd(int a, int b) {
    if (b == 0) {
        return {1, 0, a};
    } else {
        vector<int> tmp = extendGcd(b, a % b);
        return {tmp[1], tmp[0] - (a / b) * tmp[1], tmp[2]};
    }
}

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

/******************************** template ********************************/
#define N 1000010
ll n, k;
ll x[N], y[N], a[N], b[N], ia[N];
ll c, d, e[2], f;

ll power_mod(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }

    return res % MOD;
}

ll inv(ll x) {
    return power_mod(x, MOD - 2);
}

void solve() {
    cin >> n >> k >> x[1] >> y[1] >> c >> d >> e[0] >> e[1] >> f;
    go(i, 2, n) {
        x[i] = (c * x[i - 1] + d * y[i - 1] + e[0]) % f;
        y[i] = (d * x[i - 1] + c * y[i - 1] + e[1]) % f;
    }
    go(i, 1, n) a[i] = (x[i] + y[i]) % f;
    b[n] = a[n] % MOD;
    ia[n] = a[n] * n % MOD;
    gorev(i, n - 1, 1) {
        b[i] = b[i + 1] + a[i];
        ia[i] = ia[i + 1] + i * a[i];
        b[i] %= MOD;
        ia[i] %= MOD;
    }
    ll res = 0;
    go(i, 1, n) {
        ll tmp = (b[i] * (n + 1) % MOD - ia[i]) % MOD;
        if (tmp < 0) tmp += MOD;
        if (i > 1) {
            res += tmp * (power_mod(i, k) - 1 + MOD) % MOD * i % MOD * inv(i - 1) % MOD;
        } else {
            res += tmp * k % MOD;
        }
        res %= MOD;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ZYC_LOCAL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    go(t, 1, T) {
        cout << "Case #" << t << ": ";
        solve();
        cout << endl;
        cerr << t << "/" << T << " case(s) solved in " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    }

    return 0;
}
