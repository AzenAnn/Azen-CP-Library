/**
 * 02_ds/08 字典树 Trie 与 01-Trie
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 字符串 Trie：插入、前缀计数
 *   2. 01-Trie：最大异或对
 *   3. 可持久化 Trie（见 02_ds/15）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/trie/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/trie.go
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/trie01.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P8306  P8306 【模板】字典树 / Trie
 *   https://www.luogu.com.cn/problem/P4551  P4551 最长异或路径
 *   https://www.luogu.com.cn/problem/P2580  P2580 于是他错误的点名开始了
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P10471  普及  P10471 最大异或对 The XOR Largest Pair  考点：字典树 Trie
 *   https://www.luogu.com.cn/problem/P5149  普及  P5149 会议座位  考点：树状数组、排序、哈希 hashing
 *   https://www.luogu.com.cn/problem/P5266  普及  P5266 【深基17.例6】学籍管理  考点：模拟、字典树 Trie、哈希表
 *   https://www.luogu.com.cn/problem/P5755  普及  P5755 [NOI2000] 单词查找树  考点：字典树 Trie
 *   https://codeforces.com/problemset/problem/1847/C  CF1400  CF1847C Vampiric Powers, anyone?  考点：位运算、暴力、DP
 *   https://www.luogu.com.cn/problem/P1333  普及+/提高−  P1333 瑞瑞的木棍  考点：字符串、图论、并查集
 *   https://www.luogu.com.cn/problem/P1470  普及+/提高−  P1470 [IOI 1996 / USACO2.3] 最长前缀 Longest Prefix  考点：字符串、动态规划 DP、深度优先搜索 DFS
 *   https://www.luogu.com.cn/problem/P2922  普及+/提高−  P2922 [USACO08DEC] Secret Message G  考点：进制、字典树 Trie
 *   https://codeforces.com/problemset/problem/271/D  CF1800  CF271D Good Substrings  考点：数据结构、字符串
 *   https://codeforces.com/problemset/problem/706/D  CF1800  CF706D Vasiliy's Multiset  考点：二分、位运算、数据结构
 *   https://codeforces.com/problemset/problem/923/C  CF1800  CF923C Perfect Security  考点：数据结构、贪心、字符串
 *   https://codeforces.com/problemset/problem/455/B  CF1900  CF455B A Lot of Games  考点：搜索、DP、博弈
 *   https://codeforces.com/problemset/problem/514/C  CF2000  CF514C Watto and Mechanism  考点：二分、数据结构、哈希
 *   https://www.luogu.com.cn/problem/P5283  提高+/省选−  P5283 [十二省联考 2019] 异或粽子  考点：堆、可持久化、前缀和
 *   https://codeforces.com/problemset/problem/665/E  CF2100  CF665E Beautiful Subarrays  考点：数据结构、分治、字符串
 *
 */

// 1. 字符串 Trie（小写字母）：插入单词，查询单词出现次数、以某串为前缀的单词个数
//    节点 0 是根；ch[p][c] = 0 表示没有这个儿子（根不会是任何点的儿子）
struct Trie {
    vector<array<int, 26>> ch;
    vector<int> pass, ends;   // 经过该节点的单词数、在该节点结束的单词数
    Trie() { new_node(); }
    int new_node() {
        ch.push_back({});
        pass.push_back(0), ends.push_back(0);
        return ch.size() - 1;
    }
    void insert(const string &s) {
        int p = 0;
        pass[0]++;
        for (char c : s) {
            int x = c - 'a';
            if (!ch[p][x]) {
                int q = new_node();
                ch[p][x] = q;
            }
            p = ch[p][x];
            pass[p]++;
        }
        ends[p]++;
    }
    int walk(const string &s) const {   // 走到 s 对应的节点，不存在返回 -1
        int p = 0;
        for (char c : s) {
            p = ch[p][c - 'a'];
            if (!p) return -1;
        }
        return p;
    }
    int count(const string &s) const { int p = walk(s); return p < 0 ? 0 : ends[p]; }
    int prefix_count(const string &s) const { int p = walk(s); return p < 0 ? 0 : pass[p]; }
};

// 2. 01-Trie：维护一个非负整数的多重集合，求集合中与 x 异或的最大值
//    从高位到低位贪心：每一位尽量走和 x 这一位相反的方向
struct XorTrie {
    static const int B = 30;   // 数值范围 [0, 2^30)，ll 时改成 60 并把 int 换成 ll
    vector<array<int, 2>> ch;
    vector<int> cnt;           // 经过该节点的数的个数，支持删除
    XorTrie() : ch(1, {0, 0}), cnt(1, 0) {}
    void insert(int x, int delta = 1) {   // delta = -1 表示删除一个 x（x 必须在集合中）
        int p = 0;
        cnt[0] += delta;
        for (int b = B - 1; b >= 0; b--) {
            int c = x >> b & 1;
            if (!ch[p][c]) {
                ch[p][c] = ch.size();
                ch.push_back({0, 0}), cnt.push_back(0);
            }
            p = ch[p][c];
            cnt[p] += delta;
        }
    }
    int max_xor(int x) const {   // 要求集合非空
        int p = 0, res = 0;
        for (int b = B - 1; b >= 0; b--) {
            int c = x >> b & 1, q = ch[p][c ^ 1];
            if (q && cnt[q] > 0) res |= 1 << b, p = q;
            else p = ch[p][c];
        }
        return res;
    }
};
