#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int m, n; cin>>m >> n;
    vector<int>a(m),b(n);
    for(auto &x:a) cin>> x;
    for(auto &x:b) cin>> x;

    sort(a.begin(),a.end());
    ll ans  = 0;
    for(int x : b){
        int  q = upper_bound(a.begin(),a.end(),x)-a.begin();
        // 要防止越界 也就是考虑q =0 或者m 的情况
        if(q==0){
            ans += a[0]-x;
        }
        else if(q==m){
            ans +=x-a[m-1];
        }
        else{
            ans += min(a[q]-x,x-a[q-1]);
        }
    }
    cout<<ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}