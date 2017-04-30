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
#define PI acos(-1.0)

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<int>> vvi;

struct Interval {
    int start;
    int end;
    int label;
};

bool cmp1(Interval a, Interval b) {
    return a.start < b.start;
}

bool cmp2(Interval a, Interval b) {
    return a.end - a.start < b.end - b.start;
}

int main() {

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int ac, aj;
        cin >> ac >> aj;
        vector<Interval> foo(ac + aj);
        vector<int> time(2, 720);
        for (int j = 0; j < ac; ++j) {
            cin >> foo[j].start >> foo[j].end;
            foo[j].label = 0;
            time[1] -= foo[j].end - foo[j].start;
        }
        for (int j = ac; j < ac + aj; ++j) {
            cin >> foo[j].start >> foo[j].end;
            foo[j].label = 1;
            time[0] -= foo[j].end - foo[j].start;
        }
        sort(begin(foo), end(foo), cmp1);
        vector<Interval> bar;
        int res = 0;
        for (int k = 0; k < foo.size() - 1; ++k) {
            if (foo[k].label != foo[k + 1].label) {
                ++res;
            } else {
                bar.push_back({foo[k].end, foo[k + 1].start, foo[k].label});
            }
        }
        if (foo.back().label != foo[0].label) {
            ++res;
        } else {
            bar.push_back({foo.back().end, foo[0].start + 1440, foo[0].label});
        }
        sort(begin(bar), end(bar), cmp2);
        for (int l = 0; l < bar.size(); ++l) {
            int duration = bar[l].end - bar[l].start;
            if (time[1 - bar[l].label] >= duration) {
                time[1 - bar[l].label] -= duration;
            } else {
                res += 2;
            }
        }
        cout << "Case #" << i << ": " << res << endl;
    }

    return 0;
}