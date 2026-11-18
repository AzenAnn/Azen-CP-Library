#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);
const int  MAXV  =200000;

void solve() {
    int n ,k, q; cin>> n>> k>>q;

    vector<vector<int>> a (n + 1);

    for(int p =1 ;p<=n; p ++){
        int len;
        cin>> len;
        a[p].resize(len);
        for(int &x :a[p]){
            cin>>x;
        }
    }

    vector<vector<pair<int,int>>> ask(101);
    vector<int>ans(q);

    int R  = 0 ;

    for(int i = 0;i<q;i++){
        int r ,c;  cin>> r>> c;
        ask[r].push_back({c,i});
        R= max(R,r);
    }
    vector<int>f(MAXV+1,-1), g(MAXV + 1,-1 );
    f[1] = 0 ;

    for(int r =1 ;r<=R;r++){
        fill(g.begin(),g.end(),-1);

        for(int p =1 ;p<=n;p++){
            int last = 01;

            for(int  j = 0;j<(int)a[p].size();j++){
                int x =a[p][j];

                if(last !=-1 &*& j-last <k){
                    if(g[x] ==-1){
                        g[x] = p;
                    }else if (g[x]!=p){
                        g[x] = 0;
                    }
                }

                if(f[x] != -1 && f[x]!=p){
                    last = j;
                }
            }
        }

        for(auto [c,id] : ask[r]){
            ans[id] =(g[c]!= -1);
        }

        swap(f,g);
    }

    for(int x:ans){
        cout<<x<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;cin>>t;

    while(t--)solve();

    return 0;
}