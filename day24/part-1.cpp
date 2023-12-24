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
struct Object {
    ll px, py, pz;
    ll vx, vy, vz;
};
bool getRaysIntersection(const Object& ray1, const Object& ray2, double& x, double& y) {
    // 计算交点
    ll dx = ray2.px - ray1.px;
    ll dy = ray2.py - ray1.py;
    ll det = ray2.vx * ray1.vy - ray2.vy * ray1.vx;
    double u = 1.0 * (dy * ray2.vx - dx * ray2.vy) / det;
    double v = 1.0 * (dy * ray1.vx - dx * ray1.vy) / det;

    if (u >= 0 && v >= 0) {
        x = ray1.px + ray1.vx * u;
        y = ray1.py + ray1.vy * u;
        return true;
    }
    
    return false;
}
int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    vector<Object> objects;
    // pattern: px, py, pz @ vx, vy, vz
    string line;
    while (getline(cin, line) && !line.empty()) {
        Object obj;
        sscanf(line.c_str(), "%lld, %lld, %lld @ %lld, %lld, %lld", &obj.px, &obj.py, &obj.pz, &obj.vx, &obj.vy, &obj.vz);
        objects.push_back(obj);
    }
    int n = objects.size(), cnt = 0;

    double L = 200000000000000, R = 400000000000000;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double x, y;
            if (getRaysIntersection(objects[i], objects[j], x, y)) {
                if (x >= L && x <= R && y >= L && y <= R) {
                    cnt++;
                }
            }
        }
    }
    cout << cnt << endl;
    return 0;
}
