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
#define N 100010
int n, k;
ll p[N], h[N], x[N], y[N], l[N], r[N], a[5], b[5], c[5], m[5];
vector<pair<ll, ll>> tower, balloon;

void solve() {
    cin >> n >> k;
    cin >> p[1] >> p[2] >> a[1] >> b[1] >> c[1] >> m[1];
    cin >> h[1] >> h[2] >> a[2] >> b[2] >> c[2] >> m[2];
    cin >> x[1] >> x[2] >> a[3] >> b[3] >> c[3] >> m[3];
    cin >> y[1] >> y[2] >> a[4] >> b[4] >> c[4] >> m[4];
    go(i, 3, n) {
        p[i] = (a[1] * p[i - 1] + b[1] * p[i - 2] + c[1]) % m[1] + 1;
        h[i] = (a[2] * h[i - 1] + b[2] * h[i - 2] + c[2]) % m[2] + 1;
    }
    go(i, 3, k) {
        x[i] = (a[3] * x[i - 1] + b[3] * x[i - 2] + c[3]) % m[3] + 1;
        y[i] = (a[4] * y[i - 1] + b[4] * y[i - 2] + c[4]) % m[4] + 1;
    }
    tower.clear();
    balloon.clear();
    go(i, 1, n) tower.pb({p[i], h[i]});
    go(i, 1, k) balloon.pb({x[i], y[i]});
    sort(all(tower));
    sort(all(balloon));
    go(i, 0, n - 1) {
        if (!i) {
            l[i] = tower[i].fi + tower[i].se;
        } else {
            l[i] = max(l[i - 1], tower[i].fi + tower[i].se);
        }
    }
    gorev(i, n - 1, 0) {
        if (i == n - 1) {
            r[i] = tower[i].se - tower[i].fi;
        } else {
            r[i] = max(r[i + 1], tower[i].se - tower[i].fi);
        }
    }
    int cur = 0, res = 0;
    go(i, 0, k - 1) {
        while (cur < n && tower[cur].fi < balloon[i].fi) {
            ++cur;
        }
        if (cur > 0 && l[cur - 1] >= balloon[i].fi + balloon[i].se) {
            ++res;
            continue;
        }
        if (cur < n && r[cur] >= balloon[i].se - balloon[i].fi) {
            ++res;
        }
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
