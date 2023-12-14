#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <assert.h>
#include <map>
#include <set>
#define MP make_pair
#define PB emplace_back
using namespace std;
int n, m;
vector<string> mp;
map<string, int> S;
vector<int> grade;
int idx = 0, st;
int cnt() {
    int res = 0;
    for (int i = 0, sc = n; i < n; ++i, --sc) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'O') {
                res += sc;
            }
        }
    }
    return res;
}
bool one_cycle() {
    for (int i = 0; i < m; ++i) {
        int lst = 0;
        for (int j = 0; j < n; ++j) {
            if (mp[j][i] == 'O') {
                mp[lst][i] = 'O';
                if (j > lst) {
                    mp[j][i] = '.';
                }
                lst++;
            } else if (mp[j][i] == '#') {
                lst = j + 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int lst = 0;
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'O') {
                mp[i][lst] = 'O';
                if (j > lst) {
                    mp[i][j] = '.';
                }
                lst++;
            } else if (mp[i][j] == '#') {
                lst = j + 1;
            }
        }
    }

    for (int i = m - 1; i >= 0; --i) {
        int lst = n - 1;
        for (int j = n - 1; j >= 0; --j) {
            if (mp[j][i] == 'O') {
                mp[lst][i] = 'O';
                if (j < lst) {
                    mp[j][i] = '.';
                }
                lst--;
            } else if (mp[j][i] == '#') {
                lst = j - 1;
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int lst = m - 1;
        for (int j = m - 1; j >= 0; --j) {
            if (mp[i][j] == 'O') {
                mp[i][lst] = 'O';
                if (j < lst) {
                    mp[i][j] = '.';
                }
                lst--;
            } else if (mp[i][j] == '#') {
                lst = j - 1;
            }
        }
    }
    string str = "";
    for (int i = 0; i < n; ++i) {
        str += mp[i];
    }

    if (S.count(str)) {
        st = S[str];
        return true;
    }
    grade.push_back(cnt());
    S[str] = idx;
    idx++;
    return false;
}
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    while (getline(cin, line)) {
        mp.push_back(line);
    }
    n = mp.size(), m = mp[0].size();
    
    while (!one_cycle()) {}

    int len = (int)grade.size() - st;
    int left = (1000000000 - st) % len;
    if (left == 0) {
        cout << grade.back() << endl;
    } else {
        cout << grade[st + left - 1] << endl;
    }
    return 0;
}