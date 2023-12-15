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
int solve(vector<string>& maze) {
    int n = maze.size(), m = maze[0].size();
    for (int i = 0; i + 1 < m; ++i) {
        int j = i, k = i + 1;
        while (j >= 0 && k < m) {
            bool flag = true;
            for (int l = 0; l < n; ++l) {
                if (maze[l][j] != maze[l][k]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                break;
            }
            --j;
            ++k;
        }
        if (j == -1 || k == m) {
            return i + 1;
        }
    }

    for (int i = 0; i + 1 < n; ++i) {
        int j = i, k = i + 1;
        while (j >= 0 && k < n) {
            bool flag = true;
            for (int l = 0; l < m; ++l) {
                if (maze[j][l] != maze[k][l]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                break;
            }
            --j;
            ++k;
        }
        if (j == -1 || k == n) {
            return (i + 1) * 100;
        }
    }

    return 0;
}
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<string> mp;
    string line;
    int ans = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        string row;
        ss >> row;
        if (row == "") {
            int ret = solve(mp); 
            ans += ret;
            mp.clear();
        } else {
            mp.emplace_back(row);
        }
    }
    int ret = solve(mp); 
    ans += ret;
    mp.clear();

    cout << ans << endl;
    return 0;
}
