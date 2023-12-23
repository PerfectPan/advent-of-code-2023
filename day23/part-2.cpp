// TODO: 爆搜，应该不是正解
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
// 右 / 下 / 左 / 上
constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};
vector<string> vec;
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    while (getline(cin, line)) {
        vec.push_back(line);
    }
    int n = vec.size(), m = vec[0].size(), ans = -1;
    vector<vector<int>> vis(n, vector<int>(m, 0));
    function<void(int, int, int)> dfs = [&](int x, int y, int len) -> void {
        if (x == 140 && y == 139) {
            ans = max(ans, len);
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || vec[tx][ty] == '#' || vis[tx][ty]) {
                continue;
            }
            vis[tx][ty] = 1;
            dfs(tx, ty, len + 1);
            vis[tx][ty] = 0;
        }
    };
    int s = 0, e = 1;
    dfs(s, e, 0);
    cout << ans << endl;
    return 0;
}
