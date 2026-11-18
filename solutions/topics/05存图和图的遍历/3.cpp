#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

// dfs

vector<vector<int>>g; //领结表
vector<bool> vis; // vis[u] : u是否已经访问过，标记数组

void dfs(int u ){
    vis[u]= true; // 一进来先标记
    // 这里先对节点u 进行一定的处理

    for(int v: g[u]){
        if(!vis[v]) dfs(v); // 访问u的邻居中没有被访问过的
    }
}

// 可以写排序，对g[u]做处理，比如说有多个邻居时先走编号小的
// 对g[u] 进行sort就可以了

// // 连通块计数
// 从1到n以此看每个点，遇到一个还没标记的点，就说明发现了一个新的连通块
// 从他出发做一次dfs，把能到达的快都标记上，然后计数++;
int n , m;
void sol1 () {
    for(int i = 0;i<m;i++){
        int u , v; cin >> u>> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }// 建图

    vector<int>comp(n+1,-1); //comp[u] 属于第几个连通块
    // -1 表示还没访问？
    // 这里使用显示栈，而不用递归，可能是为了避免有爆栈的风险
    // 最大递归深度	建议
    // \(10^3\)	通常可以放心递归
    // \(10^4\)	简单 DFS 通常可行，但依赖环境
    // \(5\times10^4\)	开始需要谨慎
    // \(10^5\)	不建议依赖递归 DFS
    // \(2\times10^5\)	推荐显式栈或 BFS
    // \(10^6\)	基本应使用非递归方式

    // 法一、 使用递归：
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
            cnt++;
        }
    }
    cout << cnt << '\n';

    // 法二使用显示栈
    //int cnt = 0;
    stack<int> st;

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;

        cnt++;
        st.push(i);//入栈
        vis[i] = true;//标记

        while (!st.empty()) {//处理栈中元素 
            int u = st.top();
            st.pop();
            //每次取出一个，就遍历他的邻居

            for (int v : g[u]) {
                if (vis[v]) continue;// 已经访问的要跳过                    
                vis[v] = true;
                st.push(v);//没访问的，这次访问了就标记，并且加入到栈中
            }
        }
    }

    cout << cnt << '\n';
}


vector<int> belong; // 用来存放在哪个连通块中
// 定义 belong[u] 表示顶点 u 属于第几个连通分量。
// - belong[u] == 0：尚未访问该顶点。
// - belong[u] == 1：属于第 1 个连通分量。
// - belong[u] == 2：属于第 2 个连通分量。
// - 以此类推。


void dfs(int u, int id) { //带参数的dfs ，连通块编号
    belong[u] = id; // 对节点的状态处理
    for (int v : g[u]) { //深度优先，处理邻居
        if (!belong[v]) {
            dfs(v, id);
        }
    }
}

void solve() {
    cin >> n >> m;

    g.resize(n + 1);
    belong.resize(n + 1, 0); // 也可以充当标记的作用 == 0 的未访问

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!belong[i]) { // 没有访问，找到一块新的连通块
            ++cnt;
            dfs(i, cnt);
        }
    }

    cout << cnt << '\n'; //连通块个数
    // 同时也可以得到了 一些O1的判断，比如是否属于同一个连通块
    // belong[i] == belong[j] ? 
    for (int i = 1; i <= n; i++) {
        cout << belong[i] << " \n"[i == n];
    }
}

// 连通块计数的显示栈递归版本

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    vector<int> belong(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 0;
    stack<int> st;

    for (int i = 1; i <= n; i++) {
        if (belong[i]) continue;

        ++cnt; 
        st.push(i);
        belong[i] = cnt;
        //要先加，然后在赋值
        // 似乎可以写为 belong[i] = ++cnt;

        while (!st.empty()) { // 用栈来dfs搜索 永远是处理栈定元素
            int u = st.top();
            st.pop();

            for (int v : g[u]) {
                if (belong[v]) continue;
                belong[v] = cnt; // 这里的cnt无须在+1了因为都是来自先前的u 的连通块
                st.push(v);
            }
        }
    }

    cout << cnt << '\n';

    for (int i = 1; i <= n; i++) {
        cout << belong[i] << " \n"[i == n];
    }
}


/*
下面是树上的dfs
写在下一章节里面吧。

*/


void solve() {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}