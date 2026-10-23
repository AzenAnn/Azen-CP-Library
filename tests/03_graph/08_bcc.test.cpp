#include "../common.hpp"
#include "../../templates/03_graph/08_bcc.hpp"

int n;
vector<pair<int, int>> E;
// 暴力：删去点 skip、边 skip_e 后的连通块编号
vector<int> comps(int skip, int skip_e) {
    vector<int> c(n, -1);
    int k = 0;
    for (int s = 0; s < n; s++) {
        if (s == skip || c[s] != -1) continue;
        vector<int> st{s};
        c[s] = k;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int i = 0; i < (int)E.size(); i++) {
                if (i == skip_e) continue;
                auto [a, b] = E[i];
                if (a == skip || b == skip) continue;
                int v = a == u ? b : b == u ? a : -1;
                if (v != -1 && c[v] == -1) c[v] = k, st.push_back(v);
            }
        }
        k++;
    }
    return c;
}
int count_of(const vector<int> &c) { return set<int>(c.begin(), c.end()).size() - (count(c.begin(), c.end(), -1) ? 1 : 0); }

int main() {
    for (int it = 0; it < 400; it++) {
        n = rnd(1, 8);
        int m = rnd(0, 12);
        E.clear();
        BCC b(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            if (u == v) continue;   // 不测自环
            E.push_back({u, v}), b.add_edge(u, v);
        }
        m = E.size();
        b.run();
        auto base = comps(-1, -1);
        int base_cnt = count_of(base);
        for (int u = 0; u < n; u++) {
            auto c = comps(u, -1);
            bool isolated = true;
            for (auto [x, y] : E) isolated &= x != u && y != u;
            CHECK(b.is_cut[u] == (count_of(c) > base_cnt - (isolated ? 1 : 0)));
        }
        vector<bool> bridge(m);
        for (int i = 0; i < m; i++) {
            bridge[i] = count_of(comps(-1, i)) > base_cnt;
            CHECK(b.is_bridge[i] == bridge[i]);
        }
        // 边双：删掉所有桥后的连通性
        int cnt;
        auto ec = b.two_edge_components(cnt);
        vector<pair<int, int>> keep;
        for (int i = 0; i < m; i++)
            if (!bridge[i]) keep.push_back(E[i]);
        auto saveE = E;
        E = keep;
        auto kc = comps(-1, -1);
        E = saveE;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++) CHECK((ec[u] == ec[v]) == (kc[u] == kc[v]));
        // 点双：两条边在同一块 ⇔ 不存在点 w 把它们分开
        vector<int> block_of(m, -1);
        for (size_t k = 0; k < b.blocks.size(); k++) {
            set<int> s(b.blocks[k].begin(), b.blocks[k].end());
            CHECK(s.size() == b.blocks[k].size());
            for (int i = 0; i < m; i++)
                if (s.count(E[i].first) && s.count(E[i].second)) {
                    CHECK(block_of[i] == -1);
                    block_of[i] = k;
                }
        }
        for (int i = 0; i < m; i++) CHECK(block_of[i] != -1);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) {
                bool same = base[E[i].first] == base[E[j].first];
                for (int w = 0; w < n && same; w++) {
                    auto c = comps(w, -1);
                    auto rep = [&](pair<int, int> e) { return e.first == w ? e.second : e.first; };
                    if (E[i].first == w && E[i].second == w) continue;
                    if (c[rep(E[i])] != c[rep(E[j])]) same = false;
                }
                CHECK((block_of[i] == block_of[j]) == same);
            }
        // 每个孤立点单独成块
        for (int u = 0; u < n; u++) {
            bool isolated = true;
            for (auto [x, y] : E) isolated &= x != u && y != u;
            if (!isolated) continue;
            bool found = false;
            for (auto &blk : b.blocks) found |= blk == vector<int>{u};
            CHECK(found);
        }
        auto t = b.block_cut_tree();
        CHECK((int)t.size() == n + (int)b.blocks.size());
    }
    return 0;
}
