#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <map>
#define MP make_pair
#define PB emplace_back
using namespace std;
constexpr int dx[4] = { 0, 1, 0, -1 };
constexpr int dy[4] = { 1, 0, -1, 0 };
unordered_map<char, vector<pair<int, string>>> pipe = {
    { '|' , { { 1, "|LJ" }, { 3, "|7F" } } },
    { '-' , { { 0, "-7J" }, { 2, "-FL" } } },
    { 'L' , { { 0, "-7J" }, { 3, "|7F" } } },
    { 'J' , { { 2, "-FL" }, { 3, "|7F" } } },
    { '7' , { { 1, "|LJ" }, { 2, "-FL" } } },
    { 'F' , { { 0, "-7J" }, { 1, "|LJ" } } },
};
string dir = "|-LJ7F";
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<string> mp;
    string line;

    while (getline(cin, line)) {
        mp.emplace_back(line);
    }

    int n = mp.size(), m = mp[0].size();
    vector<vector<int>> G(n * m);

    auto get_id = [&](int x, int y) -> int {
        return x * m + y;
    };

    auto check_limit = [&](int x, int y) -> bool {
        return x < 0 || x >= n || y < 0 || y >= m;
    };

    int sx, sy;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'S') {
                sx = i, sy = j;
            } else if (mp[i][j] != '.') {
                int id = get_id(i, j);
                auto allow_list = pipe[mp[i][j]];
                for (auto& allow: allow_list) {
                    auto& [d, valid_ch] = allow;
                    int tx = i + dx[d];
                    int ty = j + dy[d];
                    if (check_limit(tx, ty)) {
                        continue;
                    }
                    bool flag = false;
                    for (auto& ch: valid_ch) {
                        if (ch == mp[tx][ty]) {
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) {
                        continue;
                    }
                    int nxt_id = get_id(tx, ty);
                    G[id].push_back(nxt_id);
                }
            }
        }
    }

    int mx = -1;
    int id = get_id(sx, sy);
    vector<int> vis(n * m, 0);
    vector<int> loop;
    function<void(int, int, vector<int>&)> dfs = [&](int u, int f, vector<int>& path) -> void {
        vis[u] = 1;
        path.push_back(u);
        for (int& v: G[u]) {
            if (v == f) {
                continue;
            }
            if (vis[v]) {
                if (v == id) {
                    loop = path;
                    mx = max(mx, (int)loop.size() + 1);
                }
            } else {
                dfs(v, u, path);
            }
        }
        path.pop_back();
        vis[u] = 0;
    };

    for (const auto& ch: dir) {
        mp[sx][sy] = ch;
        auto allow_list = pipe[ch];
        for (auto& allow: allow_list) {
            auto& [d, valid_ch] = allow;
            int tx = sx + dx[d];
            int ty = sy + dy[d];
            if (check_limit(tx, ty)) {
                continue;
            }
            bool flag = false;
            for (auto& ch: valid_ch) {
                if (ch == mp[tx][ty]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                continue;
            }
            int nxt_id = get_id(tx, ty);
            G[id].push_back(nxt_id);
            G[nxt_id].push_back(id);
        }
        vector<int> path;
        mx = -1;
        dfs(id, -1, path);
        if (mx != -1) {
            vector<vector<int>> block(n, vector<int>(m, 0));
            for (int i = 0; i < loop.size(); ++i) {
                int x = loop[i] / m, y = loop[i] % m;
                block[x][y] = 1;
            }
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) if (!block[i][j]) {
                    int cnt = 0;
                    int idx = j;
                    // 射线法判断点是否在多边形内部
                    while (idx < m) {
                        if (!block[i][idx]) {
                            idx++;
                            continue;
                        }
                        if (mp[i][idx] == '|') {
                            idx++;
                            cnt++;
                            continue;
                        }
                        int r = idx + 1;
                        for (; r < m && block[i][r] && mp[i][r] == '-'; ++r);
                        int len = r - idx + 1;
                        if (mp[i][idx] == 'F') {
                            if (mp[i][r] == '7') {
                                cnt += 2;
                            } else {
                                cnt += 1;
                            }
                        } else if (mp[i][idx] == 'L') {
                            if (mp[i][r] == 'J') {
                                cnt += 2;
                            } else {
                                cnt += 1;
                            }
                        }
                        idx = r + 1;
                    }
                    if (cnt & 1) {
                        ans++;
                    }
                    block[i][j] = cnt + 10;
                }
            }
            cout << ans << endl;
        }
        for (auto& allow: allow_list) {
            auto& [d, valid_ch] = allow;
            int tx = sx + dx[d];
            int ty = sy + dy[d];
            if (check_limit(tx, ty)) {
                continue;
            }
            bool flag = false;
            for (auto& ch: valid_ch) {
                if (ch == mp[tx][ty]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                continue;
            }
            int nxt_id = get_id(tx, ty);
            G[id].pop_back();
            G[nxt_id].pop_back();
        }
    }

    return 0;
}
