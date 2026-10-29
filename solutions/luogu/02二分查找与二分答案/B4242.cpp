#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int n, m ; cin >> n>> m;
    vector<int>a(n),b(m);
    for(auto &x:a)cin>>x;
    for(auto &x:b)cin>>x;

    sort(b.begin(),b.end());
    int ans = 0;
    for(int x: a){
        int q = upper_bound(b.begin(),b.end(),x) -b.begin();
        int r = 0;
        if(q==m){
            r =x -b[m-1];
        }
        else if(q==0){
            r= b[0]-x;
        }
        else {
            r = min(b[q]-x,x-b[q-1]);
        }
        ans =max(r,ans);
    }
    cout<<ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}