/**
 * 07_string/10 广义 SAM
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：07_string/08 后缀自动机（SAM）
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 广义 SAM：对多个串（或 Trie 树）建一个 SAM，匹配任意子串
 *   2. Trie 上 BFS 建 SAM：按父亲节点 last 插入，避免重复建状态
 *   3. 与普通 SAM 区别：last 更新策略、重复插入同一前缀
 *   4. 应用：多串公共子串、字典树子串统计
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/general-sam/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6139  P6139 【模板】广义后缀自动机（广义 SAM）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/316/G3  CF2400  CF316G3 Good Substrings  考点：广义 SAM + 每个状态在各串中的出现次数
 *   https://www.luogu.com.cn/problem/P2336  省选/NOI−  P2336 [SCOI2012] 喵星球上的点名  考点：后缀自动机 SAM、莫队、树状数组
 *   https://www.luogu.com.cn/problem/P3181  省选/NOI−  P3181 [HAOI2016] 找相同字符  考点：广义 SAM 上统计两个串的出现次数之积
 *   https://www.luogu.com.cn/problem/P3346  省选/NOI−  P3346 [ZJOI2015] 诸神眷顾的幻想乡  考点：叶子不超过 20 个：从每个叶子出发建 Trie，再建广义 SAM
 *   https://www.luogu.com.cn/problem/P4081  省选/NOI−  P4081 [USACO17DEC] Standing Out from the Herd P  考点：广义 SAM 标记每个状态属于哪些串
 *   https://codeforces.com/problemset/problem/204/E  CF2800  CF204E Little Elephant and Strings  考点：多串的子串出现在至少 k 个串中：广义 SAM 统计每个状态覆盖的串数
 *   https://www.luogu.com.cn/problem/P4022  NOI/NOI+/CTS  P4022 [CTSC2012] 熟悉的文章  考点：后缀自动机 SAM、字符串
 *   https://codeforces.com/problemset/problem/666/E  CF3100  CF666E Forensic Examination  考点：广义 SAM + 线段树合并
 *   https://codeforces.com/problemset/problem/1037/H  CF3200  CF1037H Security  考点：SAM + 线段树合并求字典序最小的更大子串
 *
 */

// 广义后缀自动机：对多个串（或一棵 Trie）建一个 SAM，识别所有串的所有子串。字符集为小写字母。
// 在线写法：每插入一个新串，last 回到根；extend 时若转移已存在，要么直接走过去，要么像普通 SAM 一样拆出一个克隆点，
// 这样不会产生多余的空节点。用法：GeneralSAM g; for (串 s) g.insert(s);
// 例：distinct_substrings() 求所有串的本质不同子串总数；common_substring() 求所有串的最长公共子串（串的个数 ≤ 64）。
struct GeneralSAM {
    vector<array<int, 26>> nx;
    vector<int> link, len;
    vector<unsigned long long> mask;   // 每个状态出现在哪些串里（只在 insert 时打标记，最后沿 link 树往上合并）
    int cnt_str = 0;
    GeneralSAM() { new_state(0); link[0] = -1; }
    int new_state(int l) {
        nx.push_back({}), nx.back().fill(-1), link.push_back(-1), len.push_back(l), mask.push_back(0);
        return len.size() - 1;
    }
    int clone_of(int p, int q, int c) {   // 把 q 拆成长度为 len[p] + 1 的克隆点
        int cl = new_state(len[p] + 1);
        nx[cl] = nx[q], link[cl] = link[q], mask[cl] = 0;
        for (; p != -1 && nx[p][c] == q; p = link[p]) nx[p][c] = cl;
        link[q] = cl;
        return cl;
    }
    int extend(int last, int c) {
        if (nx[last][c] != -1) {   // 这个转移已经存在（别的串插入过）
            int q = nx[last][c];
            return len[q] == len[last] + 1 ? q : clone_of(last, q, c);
        }
        int cur = new_state(len[last] + 1), p = last;
        for (; p != -1 && nx[p][c] == -1; p = link[p]) nx[p][c] = cur;
        if (p == -1) link[cur] = 0;
        else {
            int q = nx[p][c];
            link[cur] = len[q] == len[p] + 1 ? q : clone_of(p, q, c);
        }
        return cur;
    }
    void insert(const string &s) {
        int last = 0;
        for (char ch : s) last = extend(last, ch - 'a'), mask[last] |= 1ULL << (cnt_str % 64);
        cnt_str++;
    }
    ll distinct_substrings() const {
        ll r = 0;
        for (size_t v = 1; v < len.size(); v++) r += len[v] - len[link[v]];
        return r;
    }
    int common_substring() {   // 所有串的最长公共子串长度
        int n = len.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) { return len[a] > len[b]; });
        vector<unsigned long long> m = mask;
        for (int v : order)
            if (link[v] >= 0) m[link[v]] |= m[v];   // 按 len 从大到小，把标记传给 link 树上的父亲
        unsigned long long all = cnt_str >= 64 ? ~0ULL : (1ULL << cnt_str) - 1;
        int best = 0;
        for (int v = 1; v < n; v++)
            if (m[v] == all) best = max(best, len[v]);
        return best;
    }
};
