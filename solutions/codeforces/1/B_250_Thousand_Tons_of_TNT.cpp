#include <bits/stdc++.h>
using namespace std;
/*

这个题被llongmax 卡了 笑死我
*/
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int  t; cin>>t;
    while(t--){
        int  n; cin>>n;
        vector<ll>a(n);
        for(auto &x :a) cin>>x;
        ll ans = 0;
        for(int k = 1;k<=n;k++){
            if(n%k!=0) continue;
            ll mx= LLONG_MIN, mn = LLONG_MAX;
            for(int i = 0 ;i<n;i +=k){
                ll s = 0 ;
                for(int j=i;j<i+k;j++) s +=a[j];
                mx =max(mx,s) , mn =min(mn,s);
            }
            ans = max(ans,mx-mn);
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