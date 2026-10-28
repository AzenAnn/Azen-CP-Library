#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int  n ,m ; cin>> n>> m;
    vector<int>pre(n+1,0);
    for(int i=0;i<n;i++){
        int x; cin>> x;
        pre[i+1] = pre[i] +x;
    }
    int ans =INT_MAX;
    if(m==0){
        cout<<0;
        return ;
    }
    // 这里i 是左端点开始的，所以是0开始
    for(int i= 0;i<=n-m;i++){
        int l = i , r = i+m-1;
        int res = pre[r+1] -pre[l];
        ans =min(res,ans);
    }
    cout<<ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}