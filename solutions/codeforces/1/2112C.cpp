#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t ; cin>>t;
    while(t--){
        ll n; cin>>n;
        vector<ll>a(n);
        for(auto &x:a)cin>>x;
        ll ans = 0 ;
        for(int k =2;k<n;k++){
            ll need = max(a[k],a[n-1]-a[k]);
            for(int j=1;j<k;j++){
                int pos = upper_bound(a.begin(),a.begin()+j,need-a[j]) - a.begin();
                ans += j-pos;
            }
        }
        cout<<ans<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}