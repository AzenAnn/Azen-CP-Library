#include "../common.hpp"
#include "../../templates/03_graph/10_euler.hpp"

int n;
vector<pair<int, int>> E;
bool directed;
vector<int> best, cur;
vector<bool> used;
bool dfs(int u) {   // 按邻点从小到大回溯，第一条走完的路径就是字典序最小的
    if ((int)cur.size() == (int)E.size() + 1) { best = cur; return true; }
    vector<pair<int, int>> cand;   // (下一个点, 边编号)
    for (int i = 0; i < (int)E.size(); i++) {
        if (used[i]) continue;
        auto [a, b] = E[i];
        if (a == u) cand.push_back({b, i});
        else if (!directed && b == u) cand.push_back({a, i});
    }
    sort(cand.begin(), cand.end());
    for (auto [v, i] : cand) {
        used[i] = true, cur.push_back(v);
        if (dfs(v)) return true;
        used[i] = false, cur.pop_back();
    }
    return false;
}

int main() {
    for (int it = 0; it < 3000; it++) {
        n = rnd(1, 5);
        int m = rnd(1, 7);
        directed = it % 2;
        E.clear();
        for (int i = 0; i < m; i++) E.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1)});
        best.clear();
        for (int s = 0; s < n && best.empty(); s++) {
            used.assign(m, false), cur = {s};
            dfs(s);
        }
        auto got = directed ? euler_path_directed(n, E) : euler_path_undirected(n, E);
        CHECK(got == best);
    }
    return 0;
}
