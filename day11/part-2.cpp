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
#define MP make_pair
#define PB emplace_back
using namespace std;
constexpr int dx[4] = { 0, 1, 0, -1 };
constexpr int dy[4] = { 1, 0, -1, 0 };
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<string> mp;
    string line;

    while (getline(cin, line)) {
        mp.emplace_back(line);
    }

    int n = mp.size(), m = mp[0].size();
    vector<vector<pair<int, int>>> G(n, vector<pair<int, int>>(m, { -1, -1 }));
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        bool hasG = false;
        for (int j = 0; j < m; ++j) {
            hasG |= mp[i][j] == '#';
        }
        if (!hasG) {
            cur += 1000000;
        } else {
            cur += 1;
        }
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == '#') {
                G[i][j].first = cur;
            }
        }
    }

    cur = 0;
    vector<pair<int, int>> gal;
    for (int i = 0; i < m; ++i) {
        bool hasG = false;
        for (int j = 0; j < n; ++j) {
            hasG |= mp[j][i] == '#';
        }
        if (!hasG) {
            cur += 1000000;
        } else {
            cur += 1;
        }
        for (int j = 0; j < n; ++j) {
            if (mp[j][i] == '#') {
                G[j][i].second = cur;
                gal.push_back(G[j][i]);
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < gal.size(); ++i) {
        for (int j = i + 1; j < gal.size(); ++j) {
            ans += abs(gal[j].second - gal[i].second) + abs(gal[j].first - gal[i].first);
        }
    }

    cout << ans << endl;
    return 0;
}
