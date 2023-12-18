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
using ll = long long;
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    int sum = 0;

    auto getDir = [&](char ch) {
        if (ch == '0') {
            return 'R';
        }
        if (ch == '1') {
            return 'D';
        }
        if (ch == '2') {
            return 'L';
        }
        return 'U';
    };

    ll x = 0, y = 0;
    vector<pair<ll, ll>> point;
    point.push_back({ x, y });
    ll len = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        string dir, color;
        ll num;
        ss >> dir;
        ss >> num;
        ss >> color;
        int s = 2, e = 6;
        num = 0;
        for (int i = s; i <= e; ++i) {
            num = num * 16 + (color[i] >= '0' && color[i] <= '9' ? color[i] - '0' : color[i] - 'a' + 10);
        }
        if (color[7] == '0') {
            y += num;
        } else if (color[7] == '1') {
            x += num;
        } else if (color[7] == '2') {
            y -= num;
        } else {
            x -= num;
        }
        len += num;
        point.push_back({ x, y });
    }

    // 任意多边形的面积
    ll ans = 0;
    for (int i = 0; i + 1 < point.size(); ++i) {
        ll x1 = point[i].first, y1 = point[i].second;
        ll x2 = point[i + 1].first, y2 = point[i + 1].second;
        ans += x1 * y2 - x2 * y1;
    }

    ans = abs(ans) / 2LL;
    // 根据公式算出来的是以每个块中点为端点的多边型的面积
    // 然后还得加上外围的一圈
    // 外围的一圈就是 周长 / 2 再加上一个块 就行了
    // 你绕了一圈，总共转弯的度数是 360°，于是刚好多一圈，就多了一个正方形
    ans += len / 2LL + 1;

    cout << ans << endl;
    return 0;
}
