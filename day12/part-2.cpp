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
using ll = long long;
ll dp[200][100][100];
ll solve(const string& row, vector<int>& num_list) {
    memset(dp, -1, sizeof(dp));
    function<ll(int, int, int)> dfs = [&](int idx, int j, int k) -> ll {
        if (idx == -1) {
            return j == 0 && k == 0;
        }
        if (~dp[idx][j][k]) {
            return dp[idx][j][k];
        }
        ll ret = 0;
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
        string real_row = "";
        for (int i = 1; i <= 5; ++i) {
            real_row += row;
            if (i < 5) {
                real_row += "?";
            }
        }
        vector<int> origin_num_list = split(num_list, ',');
        int tn = origin_num_list.size();
        for (int i = 1; i <= 4; ++i) {
            for (int j = 0; j < tn; ++j) {
                origin_num_list.push_back(origin_num_list[j]);
            }
        } 
        mp.emplace_back(real_row);
        nums.emplace_back(origin_num_list);
    }

    ll ans = 0;
    int n = mp.size();
    for (int i = 0; i < n; ++i) {
        ans += solve(mp[i], nums[i]);
    }
    cout << ans << endl;
    
    return 0;
}
