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
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    string line;
    int ans = 0;
    while (getline(cin, line)) {
        int idx = 0, value = 0;
        while (idx < line.length()) {
            if (line[idx] == ',') {
                ans += value;
                value = 0;
            } else {
                value += line[idx];
                value = value * 17 % 256;
            }
            idx++;
        }
        ans += value;
    }

    cout << ans << endl;
    return 0;
}
