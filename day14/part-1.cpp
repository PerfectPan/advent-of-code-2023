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
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<string> mp;
    string line;
    while (getline(cin, line)) {
        mp.push_back(line);
    }
    int n = mp.size(), m = mp[0].size();
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        int lst = 0;
        for (int j = 0; j < n; ++j) {
            if (mp[j][i] == 'O') {
                ans += n - lst;
                lst++;
            } else if (mp[j][i] == '#') {
                lst = j + 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
