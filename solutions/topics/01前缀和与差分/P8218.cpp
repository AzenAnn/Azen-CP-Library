#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int n ; cin>> n;
    vector<int>a(n+2,0);
    for(int i =1 ;i<=n;i++){
        int x ; cin>> x;
        a[i+1] =a[i] +x;
        // 依旧左闭右开
    }
    int m;cin>> m;
    while(m--){
        int l , r ;cin>>  l>> r;
        cout<<a[r+1] -a[l]<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}