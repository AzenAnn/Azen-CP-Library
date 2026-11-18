#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

// BFS 

// 用队列实现
int n,s;
vector<vector<int>> g(n+1);
vector<int> dist(n+1,-1); // dist[u] =-1 ,还没找到
queue<int> q;

// 从起点s出发，到每个点最少要走几条边？

void solve() {
    dist[s] =  0;
    q.push(s);
    while(!q.empty()){ // 每次处理队列队首元素
        int u = q.front();
        q.pop();
        // 处理的意思是说 遍历队首的邻居，如果有没有访问的
        // 那就更新距离位u 的距离 +1 并且把邻居v 放到队列中去》？
        for(int v : g[u]){
            if(dist[v] == -1){
                dist[v] =dist[u]+1;
                q.push(v);
            }
        }
    }    
}




void solve() {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}