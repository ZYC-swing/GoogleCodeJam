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

/******************************** template ********************************/
#define N 20010
vi v;
vector<double> dp;
int n, k;

double power(double base, int exp) {
    double res = 1.0;
    while (exp) {
        if (exp & 1) {
            res *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ZYC_LOCAL
    freopen("B-large-practice.in", "r", stdin);
    freopen("B-large-practice.out", "w", stdout);
#endif
    int t;
    cin >> t;
    go(i, 1, t) {
        cin >> n >> k;
        double expect = 0;
        v.resize(n);
        go(j, 0, n - 1) {
            cin >> v[j];
            expect += v[j];
        }
        expect /= n;
        sort(all(v));

        double sum = 0.0;
        dp.resize(n);
        gorev(j, n - 1, 0) {
            sum += v[j];
            dp[j] = sum;
        }
        double res = expect;
        go(j, 1, k) {
            auto it = lower_bound(all(v), res);
            int pos = (int)distance(v.begin(), it);
            double p1 = 1.0 * pos / n;

            res = p1 * res + (1 - p1) * dp[pos] / (distance(it, v.end()));
        }

        printf("Case #%d: %.8lf\n", i, res);
    }

#ifdef ZYC_LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
