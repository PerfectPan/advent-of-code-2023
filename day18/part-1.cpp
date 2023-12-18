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
struct Ins {
    char dir;
    int num;
    string color;
};
vector<Ins> ins;
// 右 / 下 / 左 / 上
constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        string dir, color;
        int num;
        ss >> dir;
        ss >> num;
        ss >> color;
        ins.push_back({ dir[0], num, color });
    }
    n = 0;
    m = 0;
    int mx_n = 0, mx_m = 0, mn_n = 2000, mn_m = 2000;
    for (auto &i : ins) {
        if (i.dir == 'R') {
            m += i.num;
        } else if (i.dir == 'D') {
            n += i.num;
        } else if (i.dir == 'L') {
            m -= i.num;
        } else {
            n -= i.num;
        }

        mx_n = max(mx_n, n);
        mx_m = max(mx_m, m);
        mn_n = min(mn_n, n);
        mn_m = min(mn_m, m);
    }

    n = mx_n - mn_n;
    m = mx_m - mn_m;
    int x = abs(mn_n), y = abs(mn_m);

    vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> vis2(n + 1, vector<int>(m + 1, 0));
    vis[x][y] = 1;
    for (int i = 0; i < ins.size(); i++) {
        for (int j = 1; j <= ins[i].num; j++) {
            if (ins[i].dir == 'R') {
                y++;
            } else if (ins[i].dir == 'D') {
                x++;
            } else if (ins[i].dir == 'U') {
                x--;
            } else {
                y--;
            }
            vis[x][y] = 1;
        }
    }

    auto check = [&](int x, int y) -> bool {
        if (x < 0 || x > n || y < 0 || y > m) {
            return false;
        }
        return vis[x][y];
    };

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) if (!vis[i][j]) {
            int sj = j;
            int cnt = 0;
            while (sj <= m) {
                if (!vis[i][sj]) {
                    sj++;
                    continue;
                }
                int r = sj;
                for (; r <= m && vis[i][r]; ++r);
                if (r - sj == 1) {
                    cnt += 1;
                } else {
                    // ｜_| 或者 |-| 的才会算 2 个贡献，否则可以想成还是一个竖直的线，贡献是 1
                    if ((check(i - 1, sj) && check(i - 1, r - 1)) || (check(i + 1, sj) && check(i + 1, r - 1))) {
                        cnt += 2;
                    } else {
                        cnt += 1;
                    }
                }
                sj = r;
            }
            if (cnt & 1) {
                vis2[i][j] = 1;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (vis[i][j] || vis2[i][j]) {
                ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
