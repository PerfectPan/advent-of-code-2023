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
// "/"
constexpr int down[4] = {3, 2, 1, 0};
// "\"
constexpr int up[4] = {1, 0, 3, 2};
void clear(vector<vector<vector<int>>>& vis) {
    int n = vis.size(), m = vis[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 4; ++k) {
                vis[i][j][k] = 0;
            }
        }
    }
}
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    while (getline(cin, line)) {
        mp.push_back(line);
    }

    int n = mp.size(), m = mp[0].size();
    vector<vector<vector<int>>> vis(n, vector<vector<int>>(m, vector<int>(4, 0)));

    auto check = [&](int x, int y) -> bool {
        return !(x < 0 || x >= n || y < 0 || y >= m);
    };

    function<void(int, int, int)> dfs = [&](int x, int y, int dir) -> void {
        vis[x][y][dir] = 1;

        if (mp[x][y] == '.') {
            int tx = x + dx[dir];
            int ty = y + dy[dir];
            if (check(tx, ty) && !vis[tx][ty][dir]) {
                dfs(tx, ty, dir);
            }
        } else if (mp[x][y] == '|') {
            if (dir == 1 || dir == 3) {
                int tx = x + dx[dir];
                int ty = y + dy[dir];
                if (check(tx, ty) && !vis[tx][ty][dir]) {
                    dfs(tx, ty, dir);
                }
            } else {
                int tx = x + dx[1];
                int ty = y + dy[1];
                if (check(tx, ty) && !vis[tx][ty][1]) {
                    dfs(tx, ty, 1);
                }

                tx = x + dx[3];
                ty = y + dy[3];
                if (check(tx, ty) && !vis[tx][ty][3]) {
                    dfs(tx, ty, 3);
                }
            }
        } else if (mp[x][y] == '-') {
            if (dir == 0 || dir == 2) {
                int tx = x + dx[dir];
                int ty = y + dy[dir];
                if (check(tx, ty) && !vis[tx][ty][dir]) {
                    dfs(tx, ty, dir);
                }
            } else {
                int tx = x + dx[0];
                int ty = y + dy[0];
                if (check(tx, ty) && !vis[tx][ty][0]) {
                    dfs(tx, ty, 0);
                }

                tx = x + dx[2];
                ty = y + dy[2];
                if (check(tx, ty) && !vis[tx][ty][2]) {
                    dfs(tx, ty, 2);
                }
            }
        } else if (mp[x][y] == '/') {
            int nxt_dir = down[dir];
            int tx = x + dx[nxt_dir];
            int ty = y + dy[nxt_dir];
            if (check(tx, ty) && !vis[tx][ty][nxt_dir]) {
                dfs(tx, ty, nxt_dir);
            }
        } else {
            int nxt_dir = up[dir];
            int tx = x + dx[nxt_dir];
            int ty = y + dy[nxt_dir];
            if (check(tx, ty) && !vis[tx][ty][nxt_dir]) {
                dfs(tx, ty, nxt_dir);
            }
        }
    };

    
    auto cnt = [&]() -> int {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    cnt += vis[i][j][k];
                }
                res += cnt > 0;
            }
        }
        return res;
    };
    int ans = 0;
    for (int j = 0; j < m; ++j) {
        clear(vis);
        dfs(0, j, 1);
        ans = max(ans, cnt());
        clear(vis);
        dfs(n - 1, j, 3);
        ans = max(ans, cnt());
    }

    for (int j = 0; j < n; ++j) {
        clear(vis);
        dfs(j, 0, 0);
        ans = max(ans, cnt());
        clear(vis);
        dfs(j, m - 1, 2);
        ans = max(ans, cnt());
    }
    

    cout << ans << endl;
    return 0;
}
