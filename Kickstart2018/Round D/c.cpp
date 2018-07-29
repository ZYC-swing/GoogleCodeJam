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
#define N 101
int r, c, w;
string g[N];
ll tot[N][N][N][N];

const int dx[2] = {-1, 0};
const int dy[2] = {0, -1};

ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a % b);
}

struct TrieNode {
    TrieNode* c[26];
    bool end;
    TrieNode() : end(false) {
        go(i, 0, 25) c[i] = nullptr;
    }
};

bool valid(int x, int y) {
    return x >= 1 && x <= r && y >= 1 && y <= c;
}

struct Trie {
    TrieNode* rt;

    Trie() {
        rt = new TrieNode();
    }

    void insert(string w, int rev = 0) {
        TrieNode* cur = rt;
        int step = rev ? -1 : 1;
        for (int i = rev ? (int)w.length() - 1 : 0; i >= 0 && i < w.length(); i += step) {
            if (cur->c[w[i] - 'A'] == nullptr) {
                cur->c[w[i] - 'A'] = new TrieNode();
            }
            cur = cur->c[w[i] - 'A'];
        }
        cur->end = true;
    }

    ll search(int x, int y, int d, int step) {
        TrieNode* cur = rt;
        ll res = 0, len = 0;
        while (valid(x, y) && step) {
            if (cur->c[g[x][y] - 'A'] == nullptr) return res;
            cur = cur->c[g[x][y] - 'A'];
            ++len;
            if (cur->end) res += len;
            x += dx[d];
            y += dy[d];
            step--;
        }

        return res;
    }
};

void solve() {
    cin >> r >> c >> w;
    go(i, 1, r) {
        cin >> g[i];
        g[i].insert(g[i].begin(), '*');
    }
    string ww;
    Trie foo, bar;
    go(i, 1, w) {
        cin >> ww;
        foo.insert(ww);
        bar.insert(ww, 1);
    }
    go(i, 1, r) go(j, 1, c) go(ii, 1, i) go(jj, 1, j) {
        tot[i][j][ii][jj] = tot[i - 1][j][ii - 1][jj] + tot[i][j - 1][ii][jj - 1] - tot[i - 1][j - 1][ii - 1][jj - 1];
        tot[i][j][ii][jj] += foo.search(i, j, 0, ii) + foo.search(i, j, 1, jj)
                    + bar.search(i, j, 0, ii) + bar.search(i, j, 1, jj);
    }

    ll y = 0, z = 1, cnt = 0;
    go(x1, 1, r) go(y1, 1, c) go(x2, x1, r) go(y2, y1, c) {
        ll yy = tot[x2][y2][x2 - x1 + 1][y2 - y1 + 1];
        ll zz = x2 - x1 + 1 + y2 - y1 + 1;
        ll tmp = gcd(yy, zz);
        yy /= tmp;
        zz /= tmp;
        if (y * zz < yy * z) {
            y = yy;
            z = zz;
            cnt = 1;
        } else if (y == yy && z == zz) {
            ++cnt;
        }
    }
    cout << y << "/" << z << " " << cnt;
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
        fprintf(stderr, ">> %d/%d case(s) solved in %lf s.\r", t, T, 1.0 * clock() / CLOCKS_PER_SEC);
    }

    return 0;
}
