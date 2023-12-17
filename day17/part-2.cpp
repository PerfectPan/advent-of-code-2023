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
struct Node {
    int x, y, dir, cnt, cost;
    bool operator < (const Node& rhs) const {
        return cost > rhs.cost;
    }
};
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    int sum = 0;
    while (getline(cin, line)) {
        mp.push_back(line);
    }

    int n = mp.size(), m = mp[0].size();

    auto check = [&](int x, int y) -> bool {
        return !(x < 1 || x > n || y < 1 || y > m);
    };

    function<int(int, int, int, int)> dij = [&](int x, int y, int dir, int cnt) -> int {
        priority_queue<Node> Q;
        vector<vector<vector<vector<int>>>> dis(n + 1, vector<vector<vector<int>>>(m + 1, vector<vector<int>>(4, vector<int>(11, -1))));
        vector<vector<vector<vector<int>>>> vis(n + 1, vector<vector<vector<int>>>(m + 1, vector<vector<int>>(4, vector<int>(11, 0))));
        Q.push(Node{ x, y, dir, cnt, mp[x - 1][y - 1] - '0' });
        dis[x][y][dir][cnt] = mp[x - 1][y - 1] - '0';
        while (!Q.empty()) {
            auto node = Q.top(); Q.pop();
            int x = node.x, y = node.y, dir = node.dir, cnt = node.cnt;
            if (vis[x][y][dir][cnt]) {
                continue;
            }
            vis[x][y][dir][cnt] = 1;
            if (x == n && y == m) {
                continue;
            }

            if (cnt < 10) {
                int tx = x + dx[dir];
                int ty = y + dy[dir];
                int nxt_cost = dis[x][y][dir][cnt] + mp[tx - 1][ty - 1] - '0';
                if (check(tx, ty) && (dis[tx][ty][dir][cnt + 1] == -1 || dis[tx][ty][dir][cnt + 1] > nxt_cost)) {
                    dis[tx][ty][dir][cnt + 1] = nxt_cost;
                    Q.push(Node{ tx, ty, dir, cnt + 1, nxt_cost });
                }  
            }

            if (cnt >= 4) {
                if (dir == 0 || dir == 2) {
                    int tx = x + dx[1];
                    int ty = y + dy[1];
                    int nxt_cost = dis[x][y][dir][cnt] + mp[tx - 1][ty - 1] - '0';
                    if (check(tx, ty) && (dis[tx][ty][1][1] == -1 || dis[tx][ty][1][1] > nxt_cost)) {
                        dis[tx][ty][1][1] = nxt_cost;
                        Q.push(Node{ tx, ty, 1, 1, nxt_cost });
                    }

                    tx = x + dx[3];
                    ty = y + dy[3];
                    nxt_cost = dis[x][y][dir][cnt] + mp[tx - 1][ty - 1] - '0';
                    if (check(tx, ty) && (dis[tx][ty][3][1] == -1 || dis[tx][ty][3][1] > nxt_cost)) {
                        dis[tx][ty][3][1] = nxt_cost;
                        Q.push(Node{ tx, ty, 3, 1, nxt_cost });
                    }
                } else {
                    int tx = x + dx[0];
                    int ty = y + dy[0];
                    int nxt_cost = dis[x][y][dir][cnt] + mp[tx - 1][ty - 1] - '0';
                    if (check(tx, ty) && (dis[tx][ty][0][1] == -1 || dis[tx][ty][0][1] > nxt_cost)) {
                        dis[tx][ty][0][1] = nxt_cost;
                        Q.push(Node{ tx, ty, 0, 1, nxt_cost });
                    }

                    tx = x + dx[2];
                    ty = y + dy[2];
                    nxt_cost = dis[x][y][dir][cnt] + mp[tx - 1][ty - 1] - '0';
                    if (check(tx, ty) && (dis[tx][ty][2][1] == -1 || dis[tx][ty][2][1] > nxt_cost)) {
                        dis[tx][ty][2][1] = nxt_cost;
                        Q.push(Node{ tx, ty, 2, 1, nxt_cost });
                    }
                }
            }            
        }
        int ret = INT_MAX;

        for (int i = 0; i < 4; ++i) {
            for (int j = 4; j <= 10; ++j) if (~dis[n][m][i][j]) {
                ret = min(ret, dis[n][m][i][j]);
            }
        }
        return ret;
    };

    cout << min(dij(1, 2, 0, 1), dij(2, 1, 1, 1)) << endl;
    return 0;
}
