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

#define ll long long
#define ull unsigned long long
#define mo 1000000007

using namespace std;
typedef pair<int, int> pii;

ll moMul(ll a, ll b) {
    return ((a % mo) * (b % mo)) % mo;
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int f, s;
        cin >> f >> s;
        set<pii> foo;
        vector<int> cnt(s + 1, 0);

        for (int j = 0; j < f; ++j) {
            int a, b;
            cin >> a >> b;
            if (a == b) {
                cnt[a]++;
            } else if (foo.find(pii(a, b)) == foo.end()) {
                ++cnt[a];
                ++cnt[b];
                foo.insert(pii(a, b));
            }
        }

        int res = 0;
        for (int j = 1; j <= s; ++j) {
            res = max(res, cnt[j]);
        }

        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}