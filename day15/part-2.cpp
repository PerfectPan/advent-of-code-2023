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
vector<pair<string, int>> mp[256];
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    while (getline(cin, line)) {
        int idx = 0, value = 0, len = 0, stage = 0;
        string s = "";
        while (idx < line.length()) {
            if (line[idx] == ',') {
                if (stage == 1) {
                    bool flag = false;
                    for (int i = 0; i < mp[value].size(); ++i) {
                        if (mp[value][i].first == s) {
                            mp[value][i].second = len;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        mp[value].push_back({ s, len });
                    }
                }
                s = "";
                stage = 0;
                len = 0;
                value = 0;
            } else if (line[idx] == '-') {
                int ii = -1;
                for (int i = 0; i < mp[value].size(); ++i) {
                    if (mp[value][i].first == s) {
                        ii = i;
                        break;
                    }
                }
                if (ii != -1) {
                    mp[value].erase(mp[value].begin() + ii, mp[value].begin() + ii + 1);
                }
            } else if (line[idx] == '=') {
                stage = 1;
            }
            else {
                if (stage == 1) {
                    len = len * 10 + (line[idx] - '0');
                } else {
                    value += line[idx];
                    value = value * 17 % 256;
                    s += line[idx];
                }
            }
            idx++;
        }

        if (stage == 1) {
            bool flag = false;
            for (int i = 0; i < mp[value].size(); ++i) {
                if (mp[value][i].first == s) {
                    mp[value][i].second = len;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                mp[value].push_back({ s, len });
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < mp[i].size(); ++j) {
            ans += (i + 1) * (j + 1) * mp[i][j].second;
        }
    }
    cout << ans << endl;
    return 0;
}
