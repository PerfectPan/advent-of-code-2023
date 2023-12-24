#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <set>
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
    int sum = 0;
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
            bool flag = false;
            for (int k = j; k < r; ++k) {
                for (int l = 0; l < 8; ++l) {
                    int tx = i + dx[l];
                    int ty = k + dy[l];
                    if (tx < 0 || tx >= n || ty < 0 || ty >= m) {
                        continue;
                    }
                    if (!(mp[tx][ty] >= '0' && mp[tx][ty] <= '9') && !(mp[tx][ty] == '.')) {
                        flag = true;
                        k = r;
                        break;
                    }
                }
            }
            if (flag) {
                sum += num;
            }

            j = r;
        }
    }
    cout << sum << endl;
    return 0;
}
