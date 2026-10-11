#include "../common.hpp"
#include "../../templates/04_tree/06_tree_hash.hpp"

// 暴力：AHU 括号串。有根树的规范形 = "(" + 排序后的儿子规范形 + ")"
string canon(const vector<vector<int>> &g, int u, int p) {
    vector<string> ch;
    for (int v : g[u])
        if (v != p) ch.push_back(canon(g, v, u));
    sort(ch.begin(), ch.end());
    string s = "(";
    for (auto &c : ch) s += c;
    return s + ")";
}
string canon_unrooted(const vector<vector<int>> &g) {
    string best;
    for (int c : TreeHash::centroids(g)) {
        string s = canon(g, c, -1);
        if (best.empty() || s < best) best = s;
    }
    return best;
}
vector<vector<int>> rnd_tree(int n) {
    vector<vector<int>> g(n);
    for (int v = 1; v < n; v++) {
        int u = rnd(0, v - 1);
        g[u].push_back(v), g[v].push_back(u);
    }
    return g;
}

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 7);
        vector<vector<vector<int>>> ts;
        for (int k = 0; k < 8; k++) ts.push_back(rnd_tree(n));
        // 再加一棵打乱编号的同构树
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), test_rng);
        vector<vector<int>> h(n);
        for (int u = 0; u < n; u++)
            for (int v : ts[0][u]) h[perm[u]].push_back(perm[v]);
        ts.push_back(h);
        for (auto &a : ts)
            for (auto &b : ts) {
                CHECK((TreeHash::unrooted(a) == TreeHash::unrooted(b)) == (canon_unrooted(a) == canon_unrooted(b)));
                CHECK((TreeHash::rooted(a, 0)[0] == TreeHash::rooted(b, 0)[0]) == (canon(a, 0, -1) == canon(b, 0, -1)));
            }
        CHECK(TreeHash::unrooted(ts[0]) == TreeHash::unrooted(h));
        // 同一棵树内各子树的哈希
        auto f = TreeHash::rooted(ts[1], 0);
        vector<int> par(n, -1), order{0};
        for (size_t i = 0; i < order.size(); i++)
            for (int v : ts[1][order[i]])
                if (v != par[order[i]]) par[v] = order[i], order.push_back(v);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                CHECK((f[u] == f[v]) == (canon(ts[1], u, par[u]) == canon(ts[1], v, par[v])));
    }
    return 0;
}
