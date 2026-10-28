#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

int mon[13] ={0,31,28,31,30,31,30,31,31,30,31,30,31};
void solve() {
    int a,b,c ; char x, y;
    cin>>a>>x>>b>>y>>c;

    for(int y =1960;y<=2056;y++){
        if(y%400 ==0 || (y%4==0 && y%100!=0)){
            mon[2]= 29;
        }else{
            mon[2]=28;
        }
        for(int m = 1;m<=12;m++){
            for(int d = 1;d<=mon[m];d++){
                if(a==y%100 && b==m && c==d||
                a==m && b==d && c==y%100 ||
                a==d && b==m && c==y%100){
                    cout<<y<<"-"
                        <<setw(2)<<setfill('0')<<m<<"-"
                        <<setw(2)<<setfill('0')<<d<<'\n';
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}