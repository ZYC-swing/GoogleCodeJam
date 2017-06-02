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

#define mod 1000000007
#define PI acos(-1.0)

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

int m, n;
map<vector<int>, int> helper;
int dp[101][101];
char matrix[101][101];

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int k;
        cin >> m >> n >> k;
        for (int p = 0; p < m; ++p) {
            for (int q = 0; q < n; ++q) {
                cin >> matrix[p][q];
            }
        }
        memset(dp, 0, sizeof(dp));
        helper.clear();
        for (int row = m - 1; row >= 0; --row) {
            for (int col = 0; col < n; ++col) {
                if (matrix[row][col] == '#') {
                    if (row < m - 1 && col > 0 && col < n - 1) {
                        dp[row][col] = min(min(dp[row + 1][col - 1], dp[row + 1][col]), dp[row + 1][col + 1]);
                    }
                    ++dp[row][col];
                }
            }
        }

        int res = 0;
        vector<vector<vector<int>>> tmp(m, vector<vector<int>>(n, vector<int>(k + 1, 0)));
        for (int row = m - 1; row >= 0; --row) {
            for (int col = 0; col < n; ++col) {
                if (matrix[row][col] == '#') {
                    for (int cnt = 1; cnt <= k; ++cnt) {
                        for (int h = 1; h <= dp[row][col]; ++h) {
                            if (row + h == m) {
                                if (cnt > 1) break;
                                tmp[row][col][cnt] = max(tmp[row][col][cnt], h * h);
                            } else {
                                for (int index = col - h + 1; index <= col + h - 1; ++index) {
                                    if (cnt == 1 || tmp[row + h][index][cnt - 1]) {
                                        tmp[row][col][cnt] = max(tmp[row][col][cnt], h * h + tmp[row + h][index][cnt - 1]);
                                    }
                                }
                            }
                        }
                    }
                    if (tmp[row][col][k]) {
                        res = max(res, tmp[row][col][k]);
                    }
                }
            }
        }

        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}