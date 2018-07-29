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
#include <cstdio>
#include <ctype.h>
#include <time.h>
using namespace std;

#define PI acos(-1.0)
#define EPS 1e-8
#define MOD 1000000007
#define all(x) (x).begin(), (x).end()
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
#define N 500010
ll n, o, a, b, c, m, l;
ll d;
ll x[N], s[N], sum[N];

void solve() {
    cin >> n >> o >> d;
    cin >> x[1] >> x[2] >> a >> b >> c >> m >> l;
    go(i, 3, n) {
        x[i] = (a * x[i - 1] + b * x[i - 2] + c) % m;
    }
    go(i, 1, n) {
        s[i] = x[i] + l;
        sum[i] = sum[i - 1] + s[i];
    }

    multiset<ll> ss;

    int odd = 0, ind = 1;
    bool ok = false;
    ll res = LLONG_MIN;
    ss.insert(0);
    go(i, 1, n) {
        if (s[i] % 2 != 0) {
            ++odd;
        }
        if (odd > o) {
            while (s[ind] % 2 == 0) {
                ss.erase(ss.find(sum[ind - 1]));
                ++ind;
            }
            ss.erase(ss.find(sum[ind - 1]));
            ++ind;
            --odd;
        }
        auto tmp = ss.lower_bound(sum[i] - d);
        if (tmp != ss.end()) {
            ll foo = * tmp;
            ok = true;
            res = max(res, sum[i] - *tmp);
        }
        ss.insert(sum[i]);
    }

    if (ok) {
        cout << res;
    } else {
        cout << "IMPOSSIBLE";
    }
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
