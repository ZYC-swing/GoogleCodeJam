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
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, q;
        cin >> n >> q;
        vector<string> answer(n + 1);
        for (int j = 0; j <= n; ++j) {
            cin >> answer[j];
        }
        vector<int> score(n);
        for (int j = 0; j < n; ++j) {
            cin >> score[j];
        }

        // for small
        if (n == 1) {
            int same = 0;
            for (int j = 0; j < q; ++j) {
                if (answer[0][j] == answer.back()[j]) ++same;
            }
            cout << "Case #" << i << ": " << q - abs(same - score[0]) << endl;
        } else {// n == 2
            int a, b, c, d;//same with both; same with 0; same with 1; same with none
            a = b = c = d = 0;
            for (int j = 0; j < q; ++j) {
                if (answer[2][j] == answer[0][j]) {
                    if (answer[2][j] == answer[1][j]) {
                        ++a;
                    } else {
                        ++b;
                    }
                } else {
                    if (answer[2][j] == answer[1][j]) {
                        ++c;
                    } else {
                        ++d;
                    }
                }
            }

            int res = 0;
            for (int j = 0; j <= a; ++j) {
                for (int k = 0; k <= b; ++k) {
                    for (int l = 0; l <= c; ++l) {
                        for (int m = 0; m <= d; ++m) {
                            int right0 = j + k + (c - l) + (d - m);
                            int right1 = j + (b - k) + l + (d - m);
                            if (right0 == score[0] && right1 == score[1]) {
                                res = max(res, j + k + l + m);
                            }
                        }
                    }
                }
            }
            cout << "Case #" << i << ": " << res << endl;
        }

    }

    return 0;
}