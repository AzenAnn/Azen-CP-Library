#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int vis[1001];

void solve() {
    int n,q; scanf("%d %d",&n,&q);
    for(int i =1;i<=n;i++ ){
        int a, b ,c;
        scanf("%dx%d=%d",&a,&b,&c);
        int x = (c - b ) /a;
        vis[x] =1;
    }   

    while(q--){
        int l ,r ;
        scanf("%d %d",&l,&r);
        int cnt = 0;
        for(int i =l ; i<=r;i++){
            if(vis[i]>=1)cnt++;
        }
        printf("%d\n",cnt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}