#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);


// 在树上存图和遍历
int n; 
vector<int> parent(n + 1 , 0),order={1};
for(int i=0;i<order.size();i++){
    int u = order[i];
    for(int v :g[u]){
        if(v!= parent[u]) parent[v] =u, order.push_back(v);
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