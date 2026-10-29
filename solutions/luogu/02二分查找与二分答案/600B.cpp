#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int n,  m; cin>>n>> m;
    vector<int>a(n), b(m);
    for(auto &x:a)cin>>x;
    for(auto &x:b)cin>>x;
    sort(a.begin(),a.end());
    for(int x:b){
        int cnt = upper_bound(a.begin(),a.end(),x) -a.begin();
        cout<< cnt <<" ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}