#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int n , k , b ;cin>> n>> k>> b;
    vector<int>a(n,1);
    for(int i=0;i<b;i++){
        int x; cin>>x;
        a[x-1] = 0; // 汤碗了，第一次写成了b-1
    }
    vector<int>pre(n+1);
    for(int i= 0;i<n;i++){
        pre[i+1]  =pre[i] + a[i];
    }//
    int ans = INT_MAX;
    for(int i=0;i<n-k;i++){
        int  j = i+k;
        int res= k-( pre[j] - pre[i]);
        ans = min(ans,res);
    }
    cout<<ans;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}