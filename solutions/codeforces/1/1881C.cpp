#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);
/*
区别1base和0base的 旋转后的坐标
*/
void solve() {
   int t;   cin>> t;
    while(t--){
        int n; cin>>n ;
        vector<string>g(n);
        for(auto &x:g)cin>>x;
        ll ans = 0 ;
        for(int i =0 ;i< n/2;i++){
            for(int j  = 0;j< n/2;j++){
                int c[4] = {g[i][j],g[j][n-1-i],g[n-1-i][n-1-j],g[n-1-j][i]};
                int mx =  *max_element(c,c+4);
                for(int v: c) ans += mx-v;
            }
        }
        cout<<ans<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}