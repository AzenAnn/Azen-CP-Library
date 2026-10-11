/**
 * 07_string/08 后缀自动机（SAM）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：07_string/07 后缀数组
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. SAM 的构造
 *   2. parent 树
 *   3. 子串出现次数统计
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/sam/
 *   cp-algorithms  https://cp-algorithms.com/string/suffix-automaton.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/sam.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3804  P3804 【模板】后缀自动机（SAM）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/452/E  CF2400  CF452E Three strings  考点：数据结构、并查集、后缀结构
 *   https://www.luogu.com.cn/problem/P2336  省选/NOI−  P2336 [SCOI2012] 喵星球上的点名  考点：莫队、树状数组、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P2463  省选/NOI−  P2463 [SDOI2008] Sandy 的卡片  考点：二分、后缀自动机 SAM、哈希 hashing
 *   https://www.luogu.com.cn/problem/P3181  省选/NOI−  P3181 [HAOI2016] 找相同字符  考点：字符串、并查集、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P3649  省选/NOI−  P3649 [APIO2014] 回文串  考点：字符串、后缀自动机 SAM、后缀数组 SA
 *   https://www.luogu.com.cn/problem/P6139  省选/NOI−  P6139 【模板】广义后缀自动机（广义 SAM）  考点：后缀自动机 SAM
 *   https://codeforces.com/problemset/problem/1437/G  CF2600  CF1437G Death DBMS  考点：数据结构、后缀结构、字符串
 *   https://codeforces.com/problemset/problem/235/C  CF2700  CF235C Cyclical Quest  考点：数据结构、后缀结构、字符串
 *   https://www.luogu.com.cn/problem/P4022  NOI/NOI+/CTS  P4022 [CTSC2012] 熟悉的文章  考点：字符串、后缀自动机 SAM
 *   https://www.luogu.com.cn/problem/P4384  NOI/NOI+/CTS  P4384 [八省联考 2018] 制胡窜  考点：字符串、线段树、倍增
 *   https://www.luogu.com.cn/problem/P5115  NOI/NOI+/CTS  P5115 Check,Check,Check one two!  考点：字符串、后缀自动机 SAM、后缀数组 SA
 *   https://www.luogu.com.cn/problem/P5576  NOI/NOI+/CTS  P5576 [CmdOI2019] 口头禅  考点：后缀自动机 SAM、分治、后缀数组 SA
 *   https://www.luogu.com.cn/problem/P8368  NOI/NOI+/CTS  P8368 [LNOI2022] 串  考点：后缀自动机 SAM、后缀数组 SA、构造
 *   https://www.luogu.com.cn/problem/P8571  NOI/NOI+/CTS  P8571 [JRKSJ R6] Dedicatus545  考点：后缀自动机 SAM、分治、虚树
 *   https://www.luogu.com.cn/problem/P9348  NOI/NOI+/CTS  P9348 小园香径独徘徊  考点：字符串、贪心、后缀自动机 SAM
 *
 */

// 后缀自动机（SAM）：能识别字符串 s 所有子串的最小 DFA，状态数 <= 2n，转移数 <= 3n，线性时间构造。
// 每个状态对应一组 endpos（出现的结束位置集合）相同的子串，这些子串的长度构成区间 (len[link], len]。
// link（后缀链接）构成一棵树（parent 树），父亲的 endpos 包含儿子的 endpos。
// 只处理小写字母，状态 0 为初始状态
struct SAM {
    struct State {
        int len, link;
        array<int, 26> next;
    };
    vector<State> st;
    vector<ll> cnt;   // endpos 集合的大小 = 该状态的子串出现的次数（调用 count_endpos 后有效）
    int last = 0;
    SAM() {
        State root{0, -1, {}};
        root.next.fill(-1);
        st.push_back(root), cnt.push_back(0);
    }
    SAM(const string &s) : SAM() {
        for (char c : s) extend(c);
        count_endpos();
    }
    void extend(char ch) {
        int c = ch - 'a', cur = st.size();
        State ns{st[last].len + 1, -1, {}};
        ns.next.fill(-1);
        st.push_back(ns), cnt.push_back(1);   // 新状态对应一个新的结束位置
        int p = last;
        while (p != -1 && st[p].next[c] == -1) st[p].next[c] = cur, p = st[p].link;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {   // 把 q 拆成两个状态：clone 负责较短的那部分子串
                int clone = st.size();
                State cl = st[q];
                cl.len = st[p].len + 1;
                st.push_back(cl), cnt.push_back(0);
                while (p != -1 && st[p].next[c] == q) st[p].next[c] = clone, p = st[p].link;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    // 在 parent 树上做子树求和：按 len 从大到小（计数排序），把 cnt 加到 link 上
    void count_endpos() {
        int n = st.size(), maxlen = 0;
        for (auto &s : st) maxlen = max(maxlen, s.len);
        vector<int> bucket(maxlen + 1, 0), ord(n);
        for (auto &s : st) bucket[s.len]++;
        for (int i = 1; i <= maxlen; i++) bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--) ord[--bucket[st[i].len]] = i;
        for (int i = n - 1; i > 0; i--) cnt[st[ord[i]].link] += cnt[ord[i]];
    }
    // 1. 本质不同的子串个数 = Σ (len[v] - len[link[v]])
    ll distinct_substrings() const {
        ll r = 0;
        for (size_t v = 1; v < st.size(); v++) r += st[v].len - st[st[v].link].len;
        return r;
    }
    // 2. 子串 t 在 s 中出现的次数
    ll occurrences(const string &t) const {
        int p = 0;
        for (char c : t) {
            p = st[p].next[c - 'a'];
            if (p == -1) return 0;
        }
        return t.empty() ? 0 : cnt[p];
    }
    // 3. 洛谷 P3804：所有出现次数大于 1 的子串中，出现次数 × 长度 的最大值
    ll max_occ_times_len() const {
        ll best = 0;
        for (size_t v = 1; v < st.size(); v++)
            if (cnt[v] > 1) best = max(best, cnt[v] * st[v].len);
        return best;
    }
};
