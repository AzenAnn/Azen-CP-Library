#include "../common.hpp"
#include "../../templates/04_tree/09_prufer.hpp"

// 朴素做法：每次找编号最小的叶子
vector<int> naive_encode(const vector<int> &fa) {
    int n = fa.size();
    vector<set<int>> adj(n);
    for (int v = 0; v < n; v++)
        if (fa[v] != -1) adj[v].insert(fa[v]), adj[fa[v]].insert(v);
    vector<int> code;
    vector<bool> del(n);
    for (int k = 0; k < n - 2; k++) {
        int leaf = 0;
        while (del[leaf] || adj[leaf].size() != 1) leaf++;
        int p = *adj[leaf].begin();
        code.push_back(p), del[leaf] = true, adj[p].erase(leaf), adj[leaf].clear();
    }
    return code;
}

int main() {
    for (int it = 0; it < 3000; it++) {
        int n = rnd(2, 40);
        // 随机树，再转成以 n-1 为根的父亲数组
        vector<vector<int>> g(n);
        vector<int> perm(n);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end(), test_rng);
        for (int i = 1; i < n; i++) {
            int u = perm[i], v = perm[rnd(0, i - 1)];
            g[u].push_back(v), g[v].push_back(u);
        }
        vector<int> fa(n, -1), q = {n - 1};
        vector<bool> vis(n);
        vis[n - 1] = true;
        for (size_t h = 0; h < q.size(); h++)
            for (int v : g[q[h]])
                if (!vis[v]) vis[v] = true, fa[v] = q[h], q.push_back(v);
        auto code = prufer_encode(fa);
        CHECK(code == naive_encode(fa));
        CHECK(prufer_decode(code) == fa);
    }
    // 小 n：所有 n^(n-2) 个序列都能还原成不同的合法树（Cayley 公式）
    for (int n = 2; n <= 6; n++) {
        int total = 1;
        for (int i = 0; i < n - 2; i++) total *= n;
        set<vector<int>> trees;
        for (int x = 0; x < total; x++) {
            vector<int> code;
            for (int i = 0, y = x; i < n - 2; i++, y /= n) code.push_back(y % n);
            auto fa = prufer_decode(code);
            CHECK(fa[n - 1] == -1);
            for (int v = 0; v < n - 1; v++) {   // 每个点沿父亲能走到根
                int c = v;
                for (int k = 0; k < n && c != n - 1; k++) c = fa[c];
                CHECK(c == n - 1);
            }
            CHECK(prufer_encode(fa) == code);
            trees.insert(fa);
        }
        CHECK((int)trees.size() == total);
    }
    return 0;
}
