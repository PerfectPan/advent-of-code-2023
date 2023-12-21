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
// 右 / 下 / 左 / 上
constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    while (getline(cin, line)) {
        mp.push_back(line);
    }

    int n = mp.size(), m = mp[0].size(), s, e;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'S') {
                s = i;
                e = j;
            }
        }
    }

    queue<pair<int, int>> Q;
    Q.push({ s, e });

    for (int _ = 1; _ <= 64; ++_) {
        queue<pair<int, int>> tmp_q;
        vector<vector<int>> vis(n, vector<int>(m, 0));
        while (!Q.empty()) {
            auto& [x, y] = Q.front(); Q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || mp[nx][ny] == '#' || vis[nx][ny]) continue;
                tmp_q.push({ nx, ny });
                vis[nx][ny] = 1;
            }
        }

        Q.swap(tmp_q);
    }

    cout << Q.size() << endl;
    return 0;
}
