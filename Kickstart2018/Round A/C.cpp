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
#define L 20010
#define M 100003
int l;
string word[L];
char ch[2];
ll n, a, b, c, d;

map<ll, int> mm[26][26];

ll Hash(string str) {
    ll res = 0;
    vi foo(26, 0);
    for (char ch : str) {
        ++foo[ch - 'a'];
    }
    go(i, 0, 25) {
        res = res * M + foo[i];
        res %= MOD;
    }
    return res;
}

ll power(ll base, int exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

ll key;
void modify(int ind, int diff) {
    key += diff * power(M, 25 - ind);
    key %= MOD;
    if (key < 0) key += MOD;
}

unordered_set<int> len;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ZYC_LOCAL
    freopen("C-large-practice.in", "r", stdin);
    freopen("C-large-practice.out", "w", stdout);
#endif

    int t;
    cin >> t;
    go(i, 1, t) {
        cin >> l;
        go(j, 0, l - 1) {
            cin >> word[j];
            mm[word[j][0] - 'a'][word[j].back() - 'a'][Hash(word[j])]++;
            len.insert((int)word[j].length());
        }
        string foo;
        cin >> ch[0] >> ch[1] >> n >> a >> b >> c >> d;
        foo.pb(ch[0]);
        foo.pb(ch[1]);
        int x[2];
        x[0] = ch[0];
        x[1] = ch[1];
        go(j, 2, n - 1) {
            int xx = (a * x[1] + b * x[0] + c) % d;
            char tmp = 'a' + xx % 26;
            foo.pb(tmp);
            x[0] = x[1];
            x[1] = xx;
        }

        int res = 0;
        for (int le : len) {
            key = 0;
            go(j, 0, le - 2) {
                modify(foo[j] - 'a', 1);
            }
            go(j, le - 1, n - 1) {
                modify(foo[j] - 'a', 1);
                if (mm[foo[j - le + 1] - 'a'][foo[j] - 'a'].find(key) != mm[foo[j - le + 1] - 'a'][foo[j] - 'a'].end()) {
                    res += mm[foo[j - le + 1] - 'a'][foo[j] - 'a'][key];
                    mm[foo[j - le + 1] - 'a'][foo[j] - 'a'].erase(key);
                }
                modify(foo[j - le + 1] - 'a', -1);
            }
        }

        cout << "Case #" << i << ": " << res << endl;
        go(j, 0, 25) go(k, 0, 25) mm[j][k].clear();
        len.clear();
    }

#ifdef ZYC_LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
