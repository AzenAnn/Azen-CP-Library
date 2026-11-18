#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);


/*
存图
*/
void solve() {

// 邻接矩阵
int n; // 假设n个点
vector<vector<int>>a(n,vector<int>(n));


//邻接表
int m ; // 假设有m条边
vector<vector<int>> g(n+1);
for(int i = 0;i<m;i++){
    int  u , v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
}
//  无向边的话，反方向要再存一次，有向边只按照需求存

// 可以直接遍历从邻居节点小到达以此输出邻居

for(int u=1;u<=n;u++){
    sort(g[u].begin(),g[u].end()); // 邻居编号从小到大
    
    for(int v : g[u]){
        cout<<v<<" ";
    }
    cout<<'\n';
}

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
