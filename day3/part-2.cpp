#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#define MP make_pair
#define PB emplace_back
using namespace std;
constexpr int dx[8] = {0, 1, 0, -1, 1, -1, 1, -1};
constexpr int dy[8] = {1, 0, -1, 0, -1, 1, 1, -1};
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string s;
    vector<string> mp;
    while (cin >> s) {
        mp.emplace_back(move(s));
    }
    int n = mp.size(), m = mp[0].size();
    vector<vector<vector<int>>> res(n, vector<vector<int>>(m, vector<int>()));
    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < m) {
            if (!(mp[i][j] >= '0' && mp[i][j] <= '9')) {
                j++;
                continue;
            }
            int r = j, num = 0;
            for (; r < m && mp[i][r] >= '0' && mp[i][r] <= '9'; ++r) {
                num = num * 10 + mp[i][r] - '0';
            }
            unordered_set<int> vis;
            for (int k = j; k < r; ++k) {
                for (int l = 0; l < 8; ++l) {
                    int tx = i + dx[l];
                    int ty = k + dy[l];
                    if (tx < 0 || tx >= n || ty < 0 || ty >= m) {
                        continue;
                    }
                    if (mp[tx][ty] == '*' && !vis.count(tx * m + ty)) {
                        vis.insert(tx * m + ty);
                    }
                }
            }
            for (auto pos: vis) {
                int pos_x = pos / m, pos_y = pos % m;
                res[pos_x][pos_y].push_back(num);
            }

            j = r;
        }
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (res[i][j].size() == 2) {
                sum += res[i][j][0] * res[i][j][1];
            }
        }
    }
    cout << sum << endl;
    return 0;
}
