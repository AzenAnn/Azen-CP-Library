#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t ;cin>> t;
    while(t--){
        int n,q ;cin>> n>> q;
        vector<ll>mx(n),pre(n+1,0);
        for(int i =0;i<n;i++){ //
            ll a ;cin>> a;
            mx[i]  = max( i? mx[i-1] : 0LL,a);
            pre[i+1] = pre[i]+a; //   
        }
        for(int i=0;i<q;i++){
            ll k ; cin>> k;
            ll c = upper_bound(mx.begin(),mx.end(),k) -mx.begin();
            cout<<pre[c]<<" \n"[i==q-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}