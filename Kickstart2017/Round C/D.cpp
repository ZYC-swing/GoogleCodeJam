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

int mini, maxi, mean, median;

int solveOdd() {
    int sum = mini + maxi + median;
    int cnt = 3;
    int small = mini + median, big = maxi + median;
    if (sum == cnt * mean) {
        return cnt;
    }
    if (sum > cnt * mean) {
        if (2 * mean <= small) return INT_MAX;
        while (sum > cnt * mean) {
            sum += small;
            cnt += 2;
        }
    } else {
        if (2 * mean >= big) return INT_MAX;
        while (sum < cnt * mean) {
            sum += big;
            cnt += 2;
        }
    }
    return cnt;
}

int solveEven() {
    int sum = mini + maxi;
    int cnt = 2;
    if (sum == cnt * mean && mean == median) {
        return cnt;
    }
    sum += 2 * median;
    cnt += 2;
    if (sum == cnt * mean) {
        return cnt;
    }
    int small = mini + median, big = maxi + median;

    if (sum > cnt * mean) {
        if (2 * mean <= small) return INT_MAX;
        while (sum > cnt * mean) {
            sum += small;
            cnt += 2;
        }
    } else {
        if (2 * mean >= big) return INT_MAX;
        while (sum < cnt * mean) {
            sum += big;
            cnt += 2;
        }
    }

    return cnt;
}

int main() {
    freopen("/Users/Swing/Documents/code/googleCodeJam/D-large-practice.in", "r", stdin);
    freopen("/Users/Swing/Documents/code/googleCodeJam/D-large-practice.out", "w", stdout);
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {

        cin >> mini >> maxi >> mean >> median;

        if (mini > maxi) {
            cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
            continue;
        }

        if (mini == maxi) {
            if (mean == mini && median == mini) {
                cout << "Case #" << i << ": " << 1 << endl;
            } else {
                cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
            }
            continue;
        }

        // mini < maxi
        if (mean <= mini || mean >= maxi || median < mini || median > maxi) {
            cout << "Case #" << i << ": " << "IMPOSSIBLE" << endl;
            continue;
        }

        int res = min(solveOdd(), solveEven());

        cout << "Case #" << i << ": " << (res == INT_MAX ? "IMPOSSIBLE" : to_string(res)) << endl;

//        cout << "Case #" << i << ": " << q - abs(same - score[0]) << endl;
    }

    return 0;
}