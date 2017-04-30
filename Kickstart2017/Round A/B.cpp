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

#define ll long long
#define mo 1000000007

using namespace std;

map<pair<int, int>, bool> dp;

bool gao(string& p1, int pos1, string& p2, int pos2) {
    auto ppp = make_pair(pos1, pos2);
    if (dp.find(ppp) != dp.end()) return dp[ppp];
    if (pos1 == p1.length()) {
        while (pos2 < p2.length()) {
            if (p2[pos2] != '*') return dp[ppp] = false;
            ++pos2;
        }
        return dp[ppp] = true;
    }
    if (pos2 == p2.length()) {
        while (pos1 < p1.length()) {
            if (p1[pos1] != '*') return dp[ppp] = false;
            ++pos1;
        }
        return dp[ppp] = true;
    }

    if (p1[pos1] != '*') {
        if (p2[pos2] != '*') {
            if (p1[pos1] == p2[pos2]) {
                return dp[ppp] = gao(p1, pos1 + 1, p2, pos2 + 1);
            } else {
                return dp[ppp] = false;
            }
        } else {
            int upper = 4;
            for (int i = 0; i <= upper && pos1 + i <= p1.length(); ++i) {
                if (gao(p1, pos1 + i, p2, pos2 + 1)) return dp[ppp] = true;
                if (p1[pos1 + i] == '*') ++upper;
            }
            return dp[ppp] = false;
        }
    } else {
        if (p2[pos2] != '*') {
            int upper = 4;
            for (int i = 0; i <= upper && pos2 + i <= p2.length(); ++i) {
                if (gao(p1, pos1 + 1, p2, pos2 + i)) return dp[ppp] = true;
                if (p2[pos2 + i] == '*') ++upper;
            }
            return dp[ppp] = false;
        } else {
            return dp[ppp] = gao(p1, pos1 + 1, p2, pos2) || gao(p1, pos1, p2, pos2 + 1);
        }
    }
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string p1, p2;
        cin >> p1 >> p2;

        cout << "Case #" << i << ": " << (gao(p1, 0, p2, 0) ? "TRUE" : "FALSE") << endl;
        dp.clear();
    }

    return 0;
}