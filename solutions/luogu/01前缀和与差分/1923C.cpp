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
        int n, q; cin >> n>> q;
        vector<ll>pre(n+2,0);
        vector<int>a(n+1);
        vector<int>num(n+1,0);
        for(int i=1;i<=n;i++){
            cin>>a[i];
            pre[i+1] =pre[i] +a[i];
            num[i] =num[i-1] + (a[i]==1 ? 1 :0) ;
        }
        // cout<<"pre is \n";
        // for(auto x :pre)cout<<x<<" ";
        // cout<<'\n';
        while(q--){
            int l, r; cin>> l>> r;
            int m = r-l+1;
            ll s = pre[r+1] -pre[l]; 
            int k= num[r] -num[l-1] ; // 闭区间
            // for(int i =l;i<=r;i++){
            //     if(a[i] ==1) k++;
            // } 这里会溢出 统计区间的1 的个数即可
            if(m>=2 && s>=(m+k)){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}