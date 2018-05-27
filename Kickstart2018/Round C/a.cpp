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
#define N 1010
vi edges[N];
int deep, top, col;
int dfn[N], vis[N], low[N], sta[N], color[N];
int cnt[N];

void tarjan(int cur, int pa) {
    dfn[cur] = ++deep;
    low[cur] = deep;
    vis[cur] = 1;
    sta[++top] = cur;

    for (int next : edges[cur]) {
        if (next == pa) continue;
        if (!dfn[next]) {
            tarjan(next, cur);
            low[cur] = min(low[cur], low[next]);
        } else {
            if (vis[next]) {
                low[cur] = min(low[cur], low[next]);
            }
        }
    }

    if (dfn[cur] == low[cur]) {
        color[cur] = ++col;
        cnt[col]++;
        vis[cur] = 0;
        while (sta[top] != cur) {
            color[sta[top]] = col;
            vis[sta[top--]] = 0;
            cnt[col]++;
        }
        top--;
    }
}

void solve() {
    int n;
    cin >> n;
    int x, y;
    go(i, 0, N - 1) edges[i].clear();
    go(i, 1, n) {
        cin >> x >> y;
        edges[x].pb(y);
        edges[y].pb(x);
    }

    deep = top = col = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
    memset(low, 0, sizeof(low));
    memset(sta, 0, sizeof(sta));
    memset(color, 0, sizeof(color));
    memset(cnt, 0, sizeof(cnt));

    tarjan(1, 0);

    vi bar;
    go(i, 1, col) if (cnt[i] > 1) {
        go(j, 1, n) {
            if (color[j] == i) bar.pb(j);
        }
        break;
    }

    vi res(N, -1);
    queue<pii> qq;
    for (int i : bar) qq.push({i, 0});
    while (!qq.empty()) {
        auto pr = qq.front();
        qq.pop();
        if (res[pr.fi] != -1) continue;
        res[pr.fi] = pr.se;
        for (int next : edges[pr.fi]) {
            qq.push({next, pr.se + 1});
        }
    }

    go(i, 1, n) cout << res[i] << " \n"[i == n];
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
//        cout << endl;
        cerr << t << "/" << T << " case(s) solved in " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    }

    return 0;
}
