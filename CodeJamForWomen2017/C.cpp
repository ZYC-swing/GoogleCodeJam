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

string foo("I/O/I/O/I/O/I/O");
vector<int> indexs{0, 4, 8, 12};

void gao(int n) {
    if (n <= 14) {
        if (n > 7) {
            cout << foo << endl;
            n -= 7;
        }
        string res = foo;
        if (n % 2 == 0) res[0] = '/';
        for (int j = 0; j < 3 - n / 2; ++j) {
            res[indexs[j + 1]] = '/';
        }
        cout << res << endl;
    } else if (n <= 35) {
        cout << foo << endl;
        int more = 35 - n;
        string s1 = foo, s2 = foo;
        if (more % 2) s1[0] = '/';
        int tmp = min(3, more / 4);
        for (int j = 0; j < tmp; ++j) {
            s2[indexs[j + 1]] = '/';
        }
        more -= tmp * 4;
        if (more >= 2) {
            s2[0] = '/';
            more -= 2;
        }
        for (int k = 0; k < more / 2; ++k) {
            s1[indexs[k + 1]] = '/';
        }
        cout << s1 << endl << s2 << endl;
    } else {
        int cnt = (n + 6) / 21;
        n -= (21 * cnt - 14);
        string s1 = foo, s2 = foo;
        int more = 28 - n;
        if (more % 2) {
            s1[1] = 'I';
            more--;
        }
        if (more % 4 > 0) {
            s2[0] = '/';
        }
        int tmp = more / 4;
        for (int j = 0; j < min(3, tmp); ++j) {
            s1[indexs[j + 1]] = '/';
        }
        for (int j = 0; j < min(3, tmp - 3); ++j) {
            s2[indexs[j + 1]] = '/';
        }
        cout << s1 << endl << s2 << endl;

        for (int i = 0; i < cnt; ++i) {
            cout << foo << endl;
        }
    }
}

int main() {
    int t;

    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ":" << endl;

        int d, n;
        cin >> d >> n;
        gao(n);
    }

    return 0;
}