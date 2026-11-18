#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

/*
看了半天，但是这个题有两个要求：
1.有向图
2.遍历的时候从编号小到大
*/
void solve() {
    int n,m; cin>> n >> m;
    vector<vector<int>>g(n+1);
    for(int i=1;i<=m;i++){
        int u ,v  ;cin>> u>> v;
        g[u].push_back(v);
        // g[v].push_back(v);
    }// tu
    for(int i=1;i<=n;i++) sort(g[i].begin(),g[i].end());
    vector<int>vis(n+1,0);
    
    //dfs
    stack<int>st;
    st.push(1);

    vector<int>ans;
    while(!st.empty()){
        int u = st.top();
        st.pop();
        if(vis[u] ==1) continue;
        vis[u] =1;
        ans.push_back(u); 
        
        // sort(g[u].begin(),g[u].end());
        for(int i =(int)g[u].size()-1;i>=0;i--){
            int v=  g[u][i];
            if(!vis[v]){
                // vis[v] =1;
                st.push(v);
            }
        }
    }


    for(int x :ans)cout<<x<<" ";
    cout<<'\n';

    vis.assign(n+1,0);
    ans.clear();

    queue<int>q;
    q.push(1);
    while(!q.empty()){
        int u  =q.front();
        q.pop();
        vis[u] =1;
        ans.push_back(u);
        // sort(g[u].begin(),g[u].end());
        for(int v : g[u]){
            if(!vis[v]){
                vis[v]=1;
                    q.push(v);
            }
        }
    }
    for(int x :ans)cout<<x<<" ";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}