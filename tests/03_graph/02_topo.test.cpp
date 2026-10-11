#include "../common.hpp"
#include "../../templates/03_graph/02_topo.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 9), m = rnd(0, 15);
        vector<vector<int>> g(n);
        bool dag = rnd(0, 1);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), test_rng);
        for (int i = 0; i < m; i++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            if (dag) {
                if (a == b) continue;
                if (a > b) swap(a, b);
                g[perm[a]].push_back(perm[b]);
            } else {
                g[a].push_back(b);
            }
        }
        // 暴力：枚举所有排列，找合法拓扑序和字典序最小的那个
        vector<int> p(n), best;
        iota(p.begin(), p.end(), 0);
        do {
            vector<int> pos(n);
            for (int i = 0; i < n; i++) pos[p[i]] = i;
            bool ok = true;
            for (int u = 0; u < n; u++)
                for (int v : g[u]) ok &= pos[u] < pos[v];
            if (ok) { best = p; break; }
        } while (next_permutation(p.begin(), p.end()));
        auto order = topo_sort(g);
        if (best.empty()) {
            CHECK((int)order.size() < n);
            continue;
        }
        CHECK((int)order.size() == n);
        vector<int> pos(n);
        for (int i = 0; i < n; i++) pos[order[i]] = i;
        for (int u = 0; u < n; u++)
            for (int v : g[u]) CHECK(pos[u] < pos[v]);
        CHECK(topo_sort_min(g) == best);
        auto f = dag_longest_path(g);
        for (int u = 0; u < n; u++)
            for (int v : g[u]) CHECK(f[v] >= f[u] + 1);
    }
    return 0;
}
