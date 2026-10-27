#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);
// 如果不是3进制呢
// 每次cost 本质上是常数完成的
// 可以往哪些方向延伸贪心呢
void solve() {
    int t ; cin>>t;
    while(t--){
        ll n;cin>> n;
        ll p  = 1, cost  =3;
        ll ans=0;
        while(n){
            ll cnt = n%3;
            ans += cnt *cost;
            n/=3;
            cost = cost*3 + p;
            p*=3;
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