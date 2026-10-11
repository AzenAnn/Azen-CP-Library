/**
 * 03_graph/09 2-SAT
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：03_graph/05 强连通分量与缩点
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 拆点建蕴含图
 *   2. SCC 判定与构造方案
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/2-sat/
 *   cp-algorithms  https://cp-algorithms.com/graph/2SAT.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/graph.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4782  P4782 【模板】2-SAT
 *   https://judge.yosupo.jp/problem/two_sat  （Library Checker）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3007  提高  P3007 [USACO11JAN] The Continental Cowngress G  考点：搜索、深度优先搜索 DFS、2-SAT
 *   https://www.luogu.com.cn/problem/P4171  提高  P4171 [JSOI2010] 满汉全席  考点：图论建模、2-SAT
 *   https://www.luogu.com.cn/problem/P5782  提高  P5782 [POI 2001 R2] 和平委员会  考点：2-SAT
 *   https://codeforces.com/problemset/problem/1475/F  CF1900  CF1475F Unusual Matrix  考点：2-SAT、暴力、构造
 *   https://codeforces.com/problemset/problem/1715/D  CF1900  CF1715D 2+ doors  考点：2-SAT、位运算、图论
 *   https://codeforces.com/problemset/problem/1438/C  CF2000  CF1438C Engineer Artem  考点：2-SAT、中国剩余定理、构造
 *   https://codeforces.com/problemset/problem/468/B  CF2000  CF468B Two Sets  考点：2-SAT、搜索、并查集
 *   https://www.luogu.com.cn/problem/P3513  提高+/省选−  P3513 [POI 2011] KON-Conspiracy  考点：2-SAT、构造
 *   https://www.luogu.com.cn/problem/P3825  提高+/省选−  P3825 [NOI2017] 游戏  考点：拓扑排序、2-SAT、强连通分量
 *   https://codeforces.com/problemset/problem/1971/H  CF2100  CF1971H ±1  考点：2-SAT、搜索、图论
 *   https://www.luogu.com.cn/problem/P3209  省选/NOI−  P3209 [HNOI2010] 平面图判定  考点：线段树、并查集、图论建模
 *   https://www.luogu.com.cn/problem/P4835  省选/NOI−  P4835 [JSOI2014] 学生选课  考点：二分、2-SAT、强连通分量
 *   https://www.luogu.com.cn/problem/P6378  省选/NOI−  P6378 [PA 2010] Riddle  考点：2-SAT、Tarjan
 *   https://codeforces.com/problemset/problem/1657/F  CF2600  CF1657F Words on Tree  考点：2-SAT、搜索、并查集
 *   https://codeforces.com/problemset/problem/568/C  CF2600  CF568C New Language  考点：2-SAT、贪心
 *
 */

// 2-SAT：n 个布尔变量，若干形如 (x_i == f) 或 (x_j == g) 的子句，求一组满足所有子句的赋值。
// 点 2i + f 表示"x_i == f"。子句 a ∨ b 等价于 ¬a → b 和 ¬b → a，建成有向边。
// 有解 ⇔ 没有变量的两个取值在同一个强连通分量里。
// 构造：Tarjan 的 SCC 编号是逆拓扑序，取 SCC 编号较小（拓扑序靠后）的那个取值。O(n + m)
struct TwoSat {
    int n, timer = 0, cnt = 0;
    vector<vector<int>> g;
    vector<int> dfn, low, comp, stk;
    vector<bool> in_stk, ans;
    TwoSat(int n) : n(n), g(2 * n) {}
    void add_clause(int i, bool f, int j, bool gv) {   // (x_i == f) ∨ (x_j == gv)
        g[2 * i + !f].push_back(2 * j + gv);
        g[2 * j + !gv].push_back(2 * i + f);
    }
    void must(int i, bool f) { add_clause(i, f, i, f); }   // 强制 x_i == f
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u), in_stk[u] = true;
        for (int v : g[u]) {
            if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
            else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u]) {
            while (true) {
                int v = stk.back();
                stk.pop_back(), in_stk[v] = false, comp[v] = cnt;
                if (v == u) break;
            }
            cnt++;
        }
    }
    bool satisfiable() {   // 有解时 ans[i] 为 x_i 的取值
        dfn.assign(2 * n, 0), low.assign(2 * n, 0), comp.assign(2 * n, -1), in_stk.assign(2 * n, false);
        for (int u = 0; u < 2 * n; u++)
            if (!dfn[u]) dfs(u);
        ans.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            ans[i] = comp[2 * i + 1] < comp[2 * i];
        }
        return true;
    }
};
