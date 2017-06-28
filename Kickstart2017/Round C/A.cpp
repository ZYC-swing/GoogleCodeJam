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
    freopen("/Users/Swing/Documents/code/googleCodeJam/A-large-practice.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/A-large-practice.out", "w", stdout);
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string word;
        cin >> word;
        string res;
        int len = word.length();
        if (len % 2) {
            res = "AMBIGUOUS";
        } else {
            res.resize(len);
            res[1] = word[0];
            for (int j = 3; j < len; j += 2) {
                res[j] = (word[j - 1] + 26 - res[j - 2]) % 26 + 'A';
            }
            res[len - 2] = word[len - 1];
            for (int j = len - 4; j >= 0; j -= 2) {
                res[j] = (word[j + 1] + 26 - res[j + 2]) % 26 + 'A';
            }
        }
        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}