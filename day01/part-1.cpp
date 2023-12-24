#include<iostream>
#define MP make_pair
#define PB emplace_back
using namespace std;
typedef long long ll;
template<typename T>
inline T read(T&x){
    x=0;int f=0;char ch=getchar();
    while (ch<'0'||ch>'9') f|=(ch=='-'),ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x=f?-x:x;
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string s;
    int sum = 0;
    while (cin >> s) {
        int a = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                a = s[i] - '0';
                break;
            }
        }
        int b = 0;
        for (int i = (int)s.length() - 1; i >= 0; --i) {
            if (s[i] >= '0' && s[i] <= '9') {
                b = s[i] - '0';
                break;
            }
        }
        sum += a * 10 + b;
    }
    cout << sum << endl;
    return 0;
}
