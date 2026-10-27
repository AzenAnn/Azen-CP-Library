#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t; cin>>t;
    while(t--){
        ll n ; cin>> n;
        vector<ll>a(n);
        for(auto &x:a) cin>>x;
        ll s=0, ans = n;
        for(int i=0;i<n;i++){
            s+=a[i];
            ll thick = i+1 , len = 0 ,cur = 0;
            bool ok = true;
            for(int j=i+1;j<n;j++){
                cur += a[j];len ++;
                if(cur==s){
                    thick = max(thick,len);
                    cur = 0 , len = 0;
                }else if(cur>s){
                    ok= false;
                    break;
                }
            }
            //这里要判断ok为真 cur ==0 也就是最后一段也是正确的
            if(cur==0 && ok)ans =min(ans,thick);
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