#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int  t ;cin >> t;
    while(t--){
        ll n,k  ; cin >> n>>k;
        vector<ll>a(n);
        for(auto &x:a)cin>>x;
        ll sum =accumulate(a.begin(),a.end(),0LL);
        if(sum<=k){
            cout<<n<<'\n';
            continue;
        }
        ll ans=0;
        //wa2 猜测是括号的问题 运算符顺序
        ll f = (k+1 )/ 2 , b = k/2;
        for(int i=0;i<n && a[i]<=f;i++){
            f  -=a[i];
            ans++;
        }
        for(int i= n-1;i>=0 &*& a[i]<=b;i--){
            b -= a[i];
            ans++;
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