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

#define PI acos(-1.0)
#define all(x) (x).begin(), (x).end()
#define pb push_back

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

/* head */

#define mod 1000000007

int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/B-large-practice.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/B-large-practice.out", "w", stdout);
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<string> grid(n);
        vector<int> cntRow(n, 0), cntCol(n, 0);
        for (int r = 0; r < n; ++r) {
            cin >> grid[r];
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 'X') {
                    ++cntRow[r], ++cntCol[c];
                }
            }
        }

        int tmpR = -1;
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (cntRow[j] == 1) {
                if (tmpR == -1) {
                    tmpR = j;
                } else {
                    ok = false;
                    break;
                }
            } else if (cntRow[j] != 2) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
            continue;
        }

        int tmpC = -1;
        ok = true;
        for (int j = 0; j < n; ++j) {
            if (cntCol[j] == 1) {
                if (tmpC == -1) {
                    tmpC = j;
                } else {
                    ok = false;
                    break;
                }
            } else if (cntCol[j] != 2) {
                ok = false;
                break;
            }
        }
        if (!ok || grid[tmpR][tmpC] != 'X') {
            cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
            continue;
        }

        unordered_set<string> foo;
        for (int i = 0; i < n; ++i) {
            if (cntRow[i] == 1) continue;
            if (foo.find(grid[i]) == foo.end()) {
                foo.insert(grid[i]);
            } else {
                foo.erase(grid[i]);
            }
        }

        cout << "Case #" << i << ": " << (foo.empty() ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }

    return 0;
}