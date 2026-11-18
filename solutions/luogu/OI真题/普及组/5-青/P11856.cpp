#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

const int Mod = 998244353;

void solve() {
    int n,x,y,z; 
    cin>> n>> x>> y>>z;

    int s = x+ y+ z;
    int m = (1<< s) -1;
    int need = (1<<(z-1)) | (1<<(y+z-1)) | (1<<(s-1));

    vector<int>f(1<<s) , g(1<<s);
    f[0]  =1 ; 

    int tot = 1;

    for(int i=0 ; i <n ;i++){
        fill(g.begin(),g.end(),0);

        for(int mask = 0; mask <=m; mask++){
            if(!f[mask]) continue;

            for(int v =1 ;v<=10;v++){
                int t = ((mask << v) | (1 << (v-1))) & m; 
                if((t & need ) == need) continue;

                g[t] += f[mask];
                if(g[t] >=Mod) g[t] -= Mod;

            }
        }
        swap(f,g);
        tot = 1LL * tot * 10 %Mod;
    }
    int bad  = 0;
    for(int v : f){
        bad += v;
        if(bad>=Mod) bad-= Mod;
    }
    cout<<(tot - bad +Mod ) %Mod << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}