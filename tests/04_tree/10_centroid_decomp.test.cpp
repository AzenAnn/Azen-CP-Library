#include "../common.hpp"
#include "../../templates/04_tree/10_centroid_decomp.hpp"

int main() {
    for (int it = 0; it < 300; it++) {
        int n = rnd(1, 30);
        vector<vector<pair<int, ll>>> g(n);
        vector<vector<int>> g0(n);
        vector<vector<ll>> d(n, vector<ll>(n, -1));
        for (int v = 1; v < n; v++) {
            int u = rnd(0, v - 1);
            ll w = rnd(0, 6);
            g[u].push_back({v, w}), g[v].push_back({u, w}), g0[u].push_back(v), g0[v].push_back(u);
        }
        for (int s = 0; s < n; s++) {
            d[s][s] = 0;
            vector<int> q{s};
            for (size_t i = 0; i < q.size(); i++)
                for (auto [v, w] : g[q[i]])
                    if (d[s][v] == -1) d[s][v] = d[s][q[i]] + w, q.push_back(v);
        }
        vector<ll> ks;
        for (int i = 0; i < 20; i++) ks.push_back(rnd(0, 40));
        auto ans = path_length_exists(g, ks);
        for (int i = 0; i < 20; i++) {
            bool e = false;
            for (int a = 0; a < n; a++)
                for (int b = a + 1; b < n; b++) e |= d[a][b] == ks[i];
            CHECK(ans[i] == e);
        }
        // 点分树：每个点在点分树中的子树，是原树上包含它的连通块，且它是这个连通块的重心
        auto par = centroid_tree(g0);
        CHECK(count(par.begin(), par.end(), -1) == 1);
        for (int c = 0; c < n; c++) {
            vector<bool> in(n, false);
            for (int v = 0; v < n; v++) {
                int x = v;
                while (x != -1 && x != c) x = par[x];
                in[v] = x == c;
            }
            int tot = count(in.begin(), in.end(), true);
            // 删去 c 后，块内每个连通部分大小 <= tot / 2
            vector<bool> vis(n, false);
            vis[c] = true;
            for (int s = 0; s < n; s++) {
                if (!in[s] || vis[s]) continue;
                int sz = 0;
                vector<int> st{s};
                vis[s] = true;
                while (!st.empty()) {
                    int u = st.back();
                    st.pop_back(), sz++;
                    for (int v : g0[u])
                        if (in[v] && !vis[v]) vis[v] = true, st.push_back(v);
                }
                CHECK(sz <= tot / 2);
            }
        }
    }
    return 0;
}
