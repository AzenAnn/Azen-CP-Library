/**
 * 07_string/06 AC 自动机
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：02_ds/08 字典树 Trie 与 01-Trie、07_string/02 KMP 与前缀函数
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Trie + fail 指针
 *   2. 多模式串匹配
 *   3. fail 树上统计出现次数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/ac-automaton/
 *   cp-algorithms  https://cp-algorithms.com/string/aho_corasick.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/acam.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3808  P3808 AC 自动机（简单版）
 *   https://www.luogu.com.cn/problem/P5357  P5357 【模板】AC 自动机
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3082  提高  P3082 [USACO13MAR] Necklace G  考点：字符串、动态规划 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P3167  提高  P3167 [CQOI2014] 通配符匹配  考点：字符串、动态规划 DP、哈希 hashing
 *   https://www.luogu.com.cn/problem/P4824  提高  P4824 [USACO15FEB] Censoring S  考点：字符串、线段树、哈希 hashing
 *   https://www.luogu.com.cn/problem/P2292  提高+/省选−  P2292 [HNOI2004] L 语言  考点：动态规划 DP、AC 自动机、状压 DP
 *   https://www.luogu.com.cn/problem/P2444  提高+/省选−  P2444 [POI 2000 R1] 病毒  考点：字符串、AC 自动机
 *   https://www.luogu.com.cn/problem/P3121  提高+/省选−  P3121 [USACO15FEB] Censoring G  考点：哈希 hashing、栈、AC 自动机
 *   https://www.luogu.com.cn/problem/P3796  提高+/省选−  P3796 AC 自动机（简单版 II）  考点：字符串、字典树 Trie、AC 自动机
 *   https://www.luogu.com.cn/problem/P3966  提高+/省选−  P3966 [TJOI2013] 单词  考点：二分、AC 自动机
 *   https://www.luogu.com.cn/problem/P4052  提高+/省选−  P4052 [JSOI2007] 文本生成器  考点：动态规划 DP、AC 自动机
 *   https://codeforces.com/problemset/problem/1202/E  CF2400  CF1202E You Are Given Some Strings...  考点：暴力、后缀结构、字符串
 *   https://codeforces.com/problemset/problem/710/F  CF2400  CF710F String Set Queries  考点：暴力、数据结构、哈希
 *   https://codeforces.com/problemset/problem/696/D  CF2500  CF696D Legen...  考点：数据结构、DP、矩阵
 *   https://codeforces.com/problemset/problem/963/D  CF2500  CF963D Frequency of String  考点：哈希、后缀结构、字符串
 *   https://codeforces.com/problemset/problem/1437/G  CF2600  CF1437G Death DBMS  考点：数据结构、后缀结构、字符串
 *   https://codeforces.com/problemset/problem/1207/G  CF2700  CF1207G Indie Album  考点：数据结构、搜索、哈希
 *
 */

// AC 自动机：多模式串匹配。在所有模式串构成的 Trie 上，为每个节点求 fail 指针：
// 指向"当前串的最长的、也在 Trie 中出现的真后缀"对应的节点（与 KMP 的前缀函数类似）。
// BFS 建 fail 的同时补全转移：没有的儿子直接指向 fail 节点的对应儿子，匹配时就不用再跳 fail。
// 建立 O(Σ|模式串| · 26)，匹配 O(|文本|)。只处理小写字母，节点 0 为根
struct ACAutomaton {
    vector<array<int, 26>> ch;
    vector<int> fail, order;   // order：BFS 序（fail 指向的节点一定在前面）
    ACAutomaton() : ch(1), fail(1, 0) { ch[0].fill(0); }
    int insert(const string &s) {   // 返回模式串结尾对应的节点
        int p = 0;
        for (char c : s) {
            int x = c - 'a';
            if (!ch[p][x]) {
                ch[p][x] = ch.size();
                ch.push_back({}), ch.back().fill(0), fail.push_back(0);
            }
            p = ch[p][x];
        }
        return p;
    }
    void build() {
        queue<int> q;
        for (int x = 0; x < 26; x++)
            if (ch[0][x]) q.push(ch[0][x]);
        order.clear();
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int x = 0; x < 26; x++) {
                int v = ch[u][x];
                if (v) fail[v] = ch[fail[u]][x], q.push(v);
                else ch[u][x] = ch[fail[u]][x];
            }
        }
    }
    // 1. 每个模式串在文本中出现的次数（洛谷 P5357）。nodes[i] 为第 i 个模式串 insert 的返回值。
    //    文本走过的每个节点计数加一；一个节点被访问，意味着它在 fail 树上的所有祖先也都出现了一次，
    //    所以最后按 BFS 逆序把计数累加到 fail 节点上（fail 树上的子树求和）
    vector<ll> count_occurrences(const string &text, const vector<int> &nodes) const {
        vector<ll> cnt(ch.size(), 0);
        int p = 0;
        for (char c : text) p = ch[p][c - 'a'], cnt[p]++;
        for (int i = (int)order.size() - 1; i >= 0; i--) cnt[fail[order[i]]] += cnt[order[i]];
        vector<ll> res;
        for (int v : nodes) res.push_back(cnt[v]);
        return res;
    }
    // 2. 有多少个模式串在文本中出现过（洛谷 P3808）
    int count_appeared(const string &text, const vector<int> &nodes) const {
        auto c = count_occurrences(text, nodes);
        return count_if(c.begin(), c.end(), [](ll x) { return x > 0; });
    }
};
