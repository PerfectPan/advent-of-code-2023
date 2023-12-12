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
vector<int> split(const string& s, char delimiter) {
    vector<int> splits;
    string split;
    istringstream ss(s);
    while (getline(ss, split, delimiter)) {
        splits.push_back(stoi(split));
    }
    return splits;
}
int dp[100][100][100];
int solve(const string& row, vector<int>& num_list) {
    memset(dp, -1, sizeof(dp));
    function<int(int, int, int)> dfs = [&](int idx, int j, int k) -> int {
        if (idx == -1) {
            return j == 0 && k == 0;
        }
        if (~dp[idx][j][k]) {
            return dp[idx][j][k];
        }
        int ret = 0;
        if (row[idx] == '.') {
            if (k == num_list[j]) {
                ret = dfs(idx - 1, j, k);
            } else if (k == 0) {
                if (j > 0) {
                    ret = dfs(idx - 1, j - 1, num_list[j - 1]);
                } else {
                    ret = dfs(idx - 1, 0, 0);
                }
            }
        } else if (row[idx] == '#') {
            if (k > 0) {
                ret = dfs(idx - 1, j, k - 1);
            }
        } else {
            if (k == num_list[j]) {
                ret = dfs(idx - 1, j, k);
            } else if (k == 0) {
                if (j > 0) {
                    ret = dfs(idx - 1, j - 1, num_list[j - 1]);
                } else {
                    ret = dfs(idx - 1, 0, 0);
                }
            }

            if (k > 0) {
                ret += dfs(idx - 1, j, k - 1);
            }
        }

        dp[idx][j][k] = ret;
        return ret;
    };
    return dfs((int)row.length() - 1, (int)num_list.size() - 1, num_list.back());
}
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<string> mp;
    vector<vector<int>> nums;
    string line;

    while (getline(cin, line)) {
        stringstream ss(line);
        string row, num_list;
        ss >> row;
        ss >> num_list;
        mp.emplace_back(row);
        nums.emplace_back(split(num_list, ','));
    }

    int ans = 0, n = mp.size();
    for (int i = 0; i < n; ++i) {
        ans += solve(mp[i], nums[i]);
    }
    cout << ans << endl;
    
    return 0;
}
