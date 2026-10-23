#include "../common.hpp"
#include "../../templates/04_tree/06_long_chain.hpp"

int main() {
    for (int it = 0; it < 500; it++) {
        int n = rnd(1, 60), root = rnd(0, n - 1);
        vector<vector<int>> g(n);
        int mode = rnd(0, 2);   // 0 随机树，1 接近链，2 菊花
        for (int v = 1; v < n; v++) {
            int u = mode == 0 ? rnd(0, v - 1) : mode == 1 ? max(0, v - (int)rnd(1, 2)) : 0;
            g[u].push_back(v), g[v].push_back(u);
        }
        LongChain lc(g, root);
        vector<int> fa(n, -1), dep(n, 0), q = {root};
        for (size_t h = 0; h < q.size(); h++)
            for (int v : g[q[h]])
                if (v != fa[q[h]]) fa[v] = q[h], dep[v] = dep[q[h]] + 1, q.push_back(v);
        for (int u = 0; u < n; u++)
            for (int k = 0; k <= n; k++) {
                int x = u;
                for (int t = 0; t < k && x != -1; t++) x = fa[x];
                CHECK(lc.kth_ancestor(u, k) == x);
            }
        auto ans = lc.dominant_index();
        for (int u = 0; u < n; u++) {
            vector<int> cnt(n + 1, 0);
            for (int v = 0; v < n; v++) {   // v 在 u 子树内？
                int x = v;
                while (x != -1 && x != u) x = fa[x];
                if (x == u) cnt[dep[v] - dep[u]]++;
            }
            int best = 0;
            for (int i = 0; i <= n; i++)
                if (cnt[i] > cnt[best]) best = i;
            CHECK(ans[u] == best);
        }
    }
    return 0;
}
