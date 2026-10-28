#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);
/*
PH1Z说是可以用小根堆，但不会，二刷的时候再看

*/
ll g = 0;
void solve() {
    int m; cin>>m;
    queue<ll>q;
    while(m--){
        ll ans = 0;
        int x; cin>>x;
        if(x==1){
            q.push(g);
        }else if(x==2){
            ll t;cin>>t;
            g+=t;
        }else if(x==3){
            ll t;cin>>t;
            while(!q.empty() && (g-q.front())>=t){
                q.pop();
                ans++;
            }
            cout<<ans<<"\n";
        }
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}