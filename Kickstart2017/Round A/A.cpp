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
#define ull unsigned long long
#define mo 1000000007

using namespace std;

ll moMul(ll a, ll b) {
    return ((a % mo) * (b % mo)) % mo;
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int r, c;
        cin >> r >> c;
        ll res = 0;
        int p = min(r, c);

        ll tmp;
        if (p % 2 == 0) {
            tmp = moMul(p / 2, p + 1);
        } else {
            tmp = moMul(p, (p + 1) / 2);
        }
        res = moMul(moMul(tmp, r), c);
        ll v1 = p, v2 = p + 1, v3 = 2 * p + 1;
        if (v1 % 2 == 0) {
            v1 /= 2;
        } else {
            v2 /= 2;
        }
        if (v1 % 3 == 0) {
            v1 /= 3;
        } else if (v2 % 3 == 0) {
            v2 /= 3;
        } else {
            v3 /= 3;
        }
        res -= moMul(moMul(moMul(v1, v2), v3), r + c);
        res %= mo;
        res += moMul(tmp, tmp);
        res = (res + mo) % mo;

        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}