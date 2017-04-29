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

#define ull unsigned long long
#define mo 1000000007

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void solve(vector<vector<char>>& matrix, vector<bool>& nonempty, int r, int c) {
    for (int i = 0; i < r; ++i) {
        if (!nonempty[i]) continue;
        for (int j = 0; j < c; ++j) {
            if (matrix[i][j] == '?') {
                if (j == 0) {
                    int k;
                    for (k = j + 1; k < c; ++k) {
                        if (matrix[i][k] != '?') break;
                    }
                    for (int l = 0; l < k; ++l) {
                        matrix[i][l] = matrix[i][k];
                    }
                    j = k;
                } else {
                    matrix[i][j] = matrix[i][j - 1];
                }
            }
        }
    }
    for (int i = 0; i < r; ++i) {
        if (!nonempty[i]) {
            if (i == 0) {
                int j;
                for (j = i + 1; j < r; ++j) {
                    if (nonempty[j]) break;
                }
                for (int k = i; k < j; ++k) {
                    matrix[k] = matrix[j];
                }
                i = j;
            } else {
                matrix[i] = matrix[i - 1];
            }
        }
    }
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int r, c;
        cin >> r >> c;
        vector<vector<char>> matrix(r, vector<char>(c));
        vector<bool> nonempty(r, false);
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < c; ++k) {
                cin >> matrix[j][k];
                if (matrix[j][k] != '?') nonempty[j] = true;
            }
        }
        solve(matrix, nonempty, r, c);
        cout << "Case #" << i << ":" << endl;
        for (int j = 0; j < r; ++j) {
            for (int k = 0; k < c; ++k) {
                cout << matrix[j][k];
            }
            cout << endl;
        }
    }

    return 0;
}