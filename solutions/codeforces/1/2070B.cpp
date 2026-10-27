/*
如何写循环来描述 不在0且命令执行完？    

依旧推导数学公式，依旧分类讨论


*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);


void  solve (){
    int t ; cin>>t;
    while(t--){
        ll n ,  x, k;  string s; 
        cin>> n>>x>> k>>s;
        ll ans =0;
        auto check =  [&] (ll x){
            for(int i=0;i<n;i++){
                x += (s[i] == 'L') ? -1 : 1;
                if(x==0) return i+1;
            }
            return -1;
        };
        ll t1= check(x);
        if(t1 == -1 || t1>k ){
            cout<<0<<"\n";
            continue;
        }

        ll t2= check(0);
        ans = (t2 == -1 ) ? 1 : 1+ (k-t1)/t2;
        cout<<ans<<'\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}
// void solve() {
//     int t ;cin>>t;
//     while(t--){
//         ll n,x,k;  cin>> n>> x>> k;
//         vector<char>s(n);
//         for(auto &x:s)cin>>x;
        
//         ll ans =0, cur=0;
//         bool ok = true;
//         while(k--){
//             if(x== 0 && cur==n-1)break;  // 处于0且最后一个指令
//             if(s[cur] == 'L') x--;
//             else if(s[cur] =='R') x++;
//             if(x==0) {
//                 ans++;
//                 cur=0;
//             }
//         }
//         cout<<ans<<'\n';
//     }
// }