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
    int n = vec.size(), m = vec[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    function<int(int, int, int, int)> dfs = [&](int x, int y, int fx, int fy) -> int {
        if (~dp[x][y]) {
            return dp[x][y];
        }
        int ret = 0;
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || vec[tx][ty] == '#') {
                continue;
            }
            if (tx == fx && ty == fy) {
                continue;
            }
            if (vec[tx][ty] == '>' && i == 2) {
                continue;
            }
            if (vec[tx][ty] == 'v' && i == 3) {
                continue;
            }
            ret = max(ret, dfs(tx, ty, x, y) + 1);
        }
        return dp[x][y] = ret;
    };
    int s = 0, e = 1;
    cout << dfs(s, e, -1, -1) << endl;
    return 0;
}
