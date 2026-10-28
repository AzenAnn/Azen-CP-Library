#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t ;cin >> t;
    while(t--){
        int n;  cin>> n;
        vector<int>a(n+1);
        for(int i=1;i<=n;i++)cin>>a[i];
        int ans = 0 , bl = 1, br=1;
        for(int l =1; l<=n ;l++){
            int del = 0;
            for(int r =l+1; r<=n;r++){
                del += (a[r]>a[l]) -(a[l]>a[r]);
                if(del <ans) ans = del ,bl = l,br=r;
            }
        }
        cout<<bl<<" "<<br<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}