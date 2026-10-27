#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t ; cin >> t;
    while(t--){
        ll x, y , k; cin>> x >>y>>k;
        ll a =( x+k -1 ) /k , b = ( y+k-1) /k;
        ll ans =(a>b) ? 2*a -1 : 2*b;
        cout<<ans<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}