/**
 * 02_ds/17 Link-Cut Tree
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：02_ds/12 平衡树、04_tree/04 树链剖分
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Splay 维护实链
 *   2. access / makeroot / link / cut
 *   3. 维护路径信息
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/lct/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/link_cut_tree.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3690  P3690 【模板】动态树（LCT）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1501  省选/NOI−  P1501 [国家集训队] Tree II  考点：动态树 LCT
 *   https://www.luogu.com.cn/problem/P2147  省选/NOI−  P2147 [SDOI2008] 洞穴勘测  考点：平衡树、动态树 LCT、线段树分治
 *   https://www.luogu.com.cn/problem/P2387  省选/NOI−  P2387 [NOI2014] 魔法森林  考点：二分、生成树、动态树 LCT
 *   https://www.luogu.com.cn/problem/P3979  省选/NOI−  P3979 遥远的国度  考点：线段树、最近公共祖先 LCA、树链剖分
 *   https://www.luogu.com.cn/problem/P4219  省选/NOI−  P4219 [BJOI2014] 大融合  考点：线段树、并查集、树状数组
 *   https://www.luogu.com.cn/problem/P4234  省选/NOI−  P4234 最小差值生成树  考点：图论、并查集、枚举
 *   https://www.luogu.com.cn/problem/P4751  省选/NOI−  P4751 【模板】动态 DP（加强版）  考点：动态规划 DP、线段树、树链剖分
 *   https://www.luogu.com.cn/problem/P7735  省选/NOI−  P7735 [NOI2021] 轻重边  考点：线段树、树链剖分、动态树 LCT
 *   https://www.luogu.com.cn/problem/P4338  NOI/NOI+/CTS  P4338 [ZJOI2018] 历史  考点：树链剖分、动态树 LCT、构造
 *   https://www.luogu.com.cn/problem/P5247  NOI/NOI+/CTS  P5247 【模板】动态图连通性  考点：图论、动态树 LCT
 *   https://www.luogu.com.cn/problem/P5649  NOI/NOI+/CTS  P5649 Sone1  考点：平衡树、动态树 LCT
 *   https://www.luogu.com.cn/problem/P6292  NOI/NOI+/CTS  P6292 区间本质不同子串个数  考点：字符串、后缀自动机 SAM、动态树 LCT
 *   https://www.luogu.com.cn/problem/P7843  NOI/NOI+/CTS  P7843 「C.E.L.U-03」布尔  考点：倍增、2-SAT、动态树 LCT
 *   https://www.luogu.com.cn/problem/P9531  NOI/NOI+/CTS  P9531 [JOIST 2022] 复兴计划 / Reconstruction Project  考点：生成树、动态树 LCT、离线处理
 *   https://codeforces.com/problemset/problem/482/E  CF3200  CF482E ELCA  考点：数据结构、树
 *
 */

// Link-Cut Tree：维护一个森林，支持连边、删边、路径查询 / 修改，均摊 O(log n)（洛谷 P3690）
// 把树剖分成若干条"实链"，每条实链用一棵 Splay 维护（中序 = 深度从浅到深），
// Splay 的根用 fa 指向实链顶端的父亲（"认父不认子"）。
// 本模板维护点权的路径异或和；换成其他可合并信息只需改 pull。点编号 1..n（0 为空节点）
struct LCT {
    vector<array<int, 2>> ch;
    vector<int> fa, stk;
    vector<ll> val, sum;
    vector<char> rev;
    LCT(int n) : ch(n + 1, {0, 0}), fa(n + 1, 0), val(n + 1, 0), sum(n + 1, 0), rev(n + 1, 0) {}
    bool is_root(int x) const { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }   // 是否为所在 Splay 的根
    void pull(int x) { sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]]; }
    void flip(int x) {
        if (!x) return;
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void push(int x) {
        if (rev[x]) flip(ch[x][0]), flip(ch[x][1]), rev[x] = 0;
    }
    void rotate(int x) {
        int y = fa[x], z = fa[y], k = ch[y][1] == x;
        if (!is_root(y)) ch[z][ch[z][1] == y] = x;
        fa[x] = z;
        ch[y][k] = ch[x][k ^ 1];
        if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
        ch[x][k ^ 1] = y, fa[y] = x;
        pull(y), pull(x);
    }
    void splay(int x) {
        stk.clear();
        for (int y = x;; y = fa[y]) {   // 先从上到下下传翻转标记
            stk.push_back(y);
            if (is_root(y)) break;
        }
        while (!stk.empty()) push(stk.back()), stk.pop_back();
        while (!is_root(x)) {
            int y = fa[x], z = fa[y];
            if (!is_root(y)) rotate((ch[y][1] == x) == (ch[z][1] == y) ? y : x);
            rotate(x);
        }
    }
    void access(int x) {   // 打通根到 x 的路径，使其成为一条实链
        for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, pull(x);
    }
    void make_root(int x) { access(x), splay(x), flip(x); }   // 换根：翻转整条链
    int find_root(int x) {
        access(x), splay(x);
        while (ch[x][0]) push(x), x = ch[x][0];
        splay(x);
        return x;
    }
    void split(int x, int y) { make_root(x), access(y), splay(y); }   // 之后 y 的 Splay 就是 x-y 路径
    bool connected(int x, int y) { return find_root(x) == find_root(y); }
    bool link(int x, int y) {   // 连边 x-y；已连通时返回 false
        make_root(x);
        if (find_root(y) == x) return false;
        fa[x] = y;
        return true;
    }
    bool cut(int x, int y) {   // 删除边 x-y；边不存在时返回 false
        make_root(x);
        if (find_root(y) != x || fa[y] != x || ch[y][0]) return false;
        fa[y] = ch[x][1] = 0;
        pull(x);
        return true;
    }
    ll query(int x, int y) { split(x, y); return sum[y]; }   // 路径异或和（要求连通）
    void update(int x, ll v) { splay(x), val[x] = v, pull(x); }   // 修改点权
};
