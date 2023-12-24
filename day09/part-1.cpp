#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#define MP make_pair
#define PB emplace_back
using namespace std;
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<vector<int>> all_data;
    string line;

    while (getline(cin, line)) {
        vector<int> line_data;
        stringstream ss(line);
        int value;

        while (ss >> value) {
            line_data.push_back(value);
        }

        all_data.push_back(line_data);
    }

    function<int(vector<int>&)> getNext = [&](vector<int>& num) -> int {
        if (num.size() == 1) {
            return 0;
        }
        vector<int> diff;
        for (int i = 1; i < num.size(); ++i) {
            diff.push_back(num[i] - num[i - 1]);
        }
        int nxt = getNext(diff);

        return num.back() + nxt;
    };

    int ans = 0;
    for (int i = 0; i < all_data.size(); ++i) {
        ans += getNext(all_data[i]);
    }
    cout << ans << endl;

    return 0;
}
