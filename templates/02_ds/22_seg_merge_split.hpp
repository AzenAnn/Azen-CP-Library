/**
 * 02_ds/22 线段树合并与分裂
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/12 线段树进阶、02_ds/15 可持久化数据结构
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 线段树合并：两棵动态开点线段树对应节点递归合并，信息叠加
 *   2. 复杂度分析：合并总复杂度 O(n log n)，每个节点只会被合并一次
 *   3. 线段树分裂：按排名/值域把一棵线段树拆成两棵
 *   4. 应用：树上启发式合并的替代、维护集合的并/交/差
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/seg-merge-split/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4556  P4556 【模板】线段树合并 / [Vani 有约会] 雨天的尾巴
 *   https://www.luogu.com.cn/problem/P5494  P5494 【模板】线段树分裂
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3201  提高  P3201 [HNOI2009] 梦幻布丁  考点：线段树合并、线段树、平衡树
 *   https://www.luogu.com.cn/problem/P3605  提高  P3605 [USACO17JAN] Promotion Counting P  考点：线段树合并、线段树、树状数组
 *   https://www.luogu.com.cn/problem/P2824  提高+/省选−  P2824 [HEOI2016/TJOI2016] 排序  考点：二分答案 + 01 序列，或线段树分裂与合并
 *   https://www.luogu.com.cn/problem/P3224  提高+/省选−  P3224 [HNOI2012] 永无乡  考点：线段树合并、线段树、并查集
 *   https://www.luogu.com.cn/problem/P3521  提高+/省选−  P3521 [POI 2011] ROT-Tree Rotations  考点：线段树合并、线段树、树上启发式合并
 *   https://codeforces.com/problemset/problem/600/E  CF2300  CF600E Lomsat gelral  考点：每棵子树的众数：线段树合并或 dsu on tree
 *   https://www.luogu.com.cn/problem/P1600  省选/NOI−  P1600 [NOIP 2016 提高组] 天天爱跑步  考点：线段树合并、线段树、树上启发式合并
 *   https://www.luogu.com.cn/problem/P4577  省选/NOI−  P4577 [FJOI2018] 领导集团问题  考点：线段树合并、线段树、树形 DP
 *   https://www.luogu.com.cn/problem/P5298  省选/NOI−  P5298 [PKUWC2018] Minimax  考点：线段树合并、线段树、树形 DP
 *   https://www.luogu.com.cn/problem/P6773  省选/NOI−  P6773 [NOI2020] 命运  考点：线段树合并、动态规划 DP、动态规划优化
 *   https://www.luogu.com.cn/problem/P6847  省选/NOI−  P6847 [CEOI 2019] Magic Tree  考点：线段树合并、动态规划 DP、贪心
 *
 */

// 权值线段树的合并与分裂（动态开点，所有树共用一个节点池）。值域 [0, V)，每棵树就是一个可重集合。
// 合并：两棵树对应节点递归相加，总复杂度 O(n log V)（每次合并都会消耗掉节点）；
// 分裂：按"前 k 小"或"≤ v"把一棵树拆成两棵，O(log V)，只新建 O(log V) 个节点。
struct SegMergeSplit {
    int V;
    vector<int> lc, rc;
    vector<ll> cnt, sum;
    SegMergeSplit(int V) : V(V), lc(1, 0), rc(1, 0), cnt(1, 0), sum(1, 0) {}   // 0 号为空节点
    int new_node() {
        lc.push_back(0), rc.push_back(0), cnt.push_back(0), sum.push_back(0);
        return lc.size() - 1;
    }
    void pull(int p) { cnt[p] = cnt[lc[p]] + cnt[rc[p]], sum[p] = sum[lc[p]] + sum[rc[p]]; }
    // 往树 root 里加入 c 个值 x，返回新根（root = 0 表示空树）
    int insert(int root, int x, ll c = 1) {
        if (!root) root = new_node();
        vector<int> path;
        int p = root, l = 0, r = V - 1;
        while (true) {
            path.push_back(p);
            if (l == r) break;
            int m = (l + r) / 2;
            if (x <= m) {
                if (!lc[p]) { int q = new_node(); lc[p] = q; }
                p = lc[p], r = m;
            } else {
                if (!rc[p]) { int q = new_node(); rc[p] = q; }
                p = rc[p], l = m + 1;
            }
        }
        cnt[p] += c, sum[p] += (ll)x * c;
        for (int i = (int)path.size() - 2; i >= 0; i--) pull(path[i]);
        return root;
    }
    // 1. 合并：把 b 并入 a，返回新根（之后 b 不能再单独使用）
    int merge(int a, int b, int l = 0, int r = -1) {
        if (r == -1) r = V - 1;
        if (!a || !b) return a | b;
        if (l == r) {
            cnt[a] += cnt[b], sum[a] += sum[b];
            return a;
        }
        int m = (l + r) / 2;
        int L = merge(lc[a], lc[b], l, m);
        int R = merge(rc[a], rc[b], m + 1, r);
        lc[a] = L, rc[a] = R;
        pull(a);
        return a;
    }
    // 2. 按个数分裂：把树 p 中最小的 k 个元素留在 p，其余放进返回的新树
    int split_k(int p, ll k, int l = 0, int r = -1) {
        if (r == -1) r = V - 1;
        if (!p || k >= cnt[p]) return 0;
        int q = new_node();
        if (l == r) {   // 叶子：同一个值拆成两份
            ll c = cnt[p] - k;
            cnt[q] = c, sum[q] = (ll)l * c;
            cnt[p] = k, sum[p] = (ll)l * k;
            return q;
        }
        int m = (l + r) / 2;
        ll lcnt = cnt[lc[p]];
        if (k <= lcnt) {   // 右子树整个归新树，左子树继续拆
            rc[q] = rc[p], rc[p] = 0;
            int t = split_k(lc[p], k, l, m);
            lc[q] = t;
        } else {
            int t = split_k(rc[p], k - lcnt, m + 1, r);
            rc[q] = t;
        }
        pull(p), pull(q);
        return q;
    }
    // 按值分裂：≤ v 的留在 p，> v 的放进返回的新树
    int split_val(int p, int v) { return split_k(p, count(p, 0, v)); }
    // 3. 查询：值在 [a, b] 内的个数 / 和，第 k 小（k 从 1 开始，要求 k ≤ 总数）
    ll count(int p, int a, int b, int l = 0, int r = -1) {
        if (r == -1) r = V - 1;
        if (!p || b < l || r < a || a > b) return 0;
        if (a <= l && r <= b) return cnt[p];
        int m = (l + r) / 2;
        return count(lc[p], a, b, l, m) + count(rc[p], a, b, m + 1, r);
    }
    ll range_sum(int p, int a, int b, int l = 0, int r = -1) {
        if (r == -1) r = V - 1;
        if (!p || b < l || r < a || a > b) return 0;
        if (a <= l && r <= b) return sum[p];
        int m = (l + r) / 2;
        return range_sum(lc[p], a, b, l, m) + range_sum(rc[p], a, b, m + 1, r);
    }
    int kth(int p, ll k) {
        int l = 0, r = V - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (k <= cnt[lc[p]]) p = lc[p], r = m;
            else k -= cnt[lc[p]], p = rc[p], l = m + 1;
        }
        return l;
    }
};
