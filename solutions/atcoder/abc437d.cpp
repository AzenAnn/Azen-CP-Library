#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);
// 思考这个题的前缀和的板子带来了什么样的好结果？

ll mod = 998244353;


void solve() {
    ll n ,m ; cin >> n >>m;
    vector<ll>a(n),b(m);  
    for(auto &x:a)cin>>x;
    for(auto &x:b)cin>>x;
    
    sort(b.begin(),b.end());
    vector<ll>pre(m+1,0);
    for(int i=0;i<m;i++){
        pre[i +1 ] = pre[i] + b[i];
    }
    ll ans =0;
    for(int i =0;i<n;i++){
        ll x=  a[i];
        auto c = upper_bound(b.begin(),b.end(),x) - b.begin();
        ans += c*x -pre[c] + (pre[m] -pre[c] - (m-c)*x);
        ans  =ans %mod;
    }
    cout<<ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}