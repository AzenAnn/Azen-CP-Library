/**
 * 04_tree/09 Prüfer 序列
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：04_tree/01 树的基础：直径、重心、DFS 序、05_math/05 组合数与计数原理
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 建序列：每次删去编号最小的叶子，记下它的邻居，直到剩两个点；得到长度 n−2 的序列
 *   2. 线性做法：用指针从小到大找叶子，删掉一个叶子后若邻居变成更小的叶子就立刻处理它，O(n)
 *   3. 还原：度数 = 在序列中出现次数 + 1，同样用指针线性还原
 *   4. Cayley 公式：n 个点的有标号无根树有 n^(n−2) 棵；度数为 d_1..d_n 的树有 (n−2)! / Π(d_i − 1)! 棵
 *   5. 推广：k 个连通块（大小 s_1..s_k）连成一棵树的方案数 = n^(k−2) · Π s_i（CF156D Clues）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/prufer/
 *   cp-algorithms  https://cp-algorithms.com/graph/pruefer_code.html
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6086  P6086 【模板】Prüfer（Prufer）序列
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2817  普及  P2817 宋荣子的城堡  考点：Prüfer 序列、数学
 *   https://www.luogu.com.cn/problem/P4981  普及  P4981 父子  考点：Prüfer 序列、组合数学
 *   https://www.luogu.com.cn/problem/P4430  普及+/提高−  P4430 小猴打架  考点：Prüfer 序列、数学、生成树
 *   https://www.luogu.com.cn/problem/P9619  普及+/提高−  P9619 生成树  考点：Prüfer 序列、数学、生成树
 *   https://www.luogu.com.cn/problem/P2290  提高  P2290 [HNOI2004] 树的计数  考点：Prüfer 序列、数学、组合数学
 *   https://www.luogu.com.cn/problem/P2624  省选/NOI−  P2624 [HNOI2008] 明明的烦恼  考点：Prüfer 序列、高精度、素数判断
 *   https://www.luogu.com.cn/problem/P5219  省选/NOI−  P5219 无聊的水题 I  考点：Prüfer 序列、生成函数、快速数论变换 NTT
 *   https://codeforces.com/problemset/problem/156/D  CF2500  CF156D Clues  考点：连通块缩点后的生成树计数 n^(k−2)·Π s_i
 *   https://codeforces.com/problemset/problem/917/D  CF2600  CF917D Stranger Trees  考点：树的计数 + 二项式反演 / 矩阵树定理
 *
 */

// 点编号 0..n-1。树用父亲数组表示：以 n-1 为根，fa[n-1] = -1（与 P6086 的约定一致，只是编号从 0 开始）。
// 1. 树 → Prüfer 序列（长度 n-2），O(n)
vector<int> prufer_encode(const vector<int> &fa) {
    int n = fa.size();
    vector<int> deg(n, 0), code;
    for (int v = 0; v < n; v++)
        if (fa[v] != -1) deg[v]++, deg[fa[v]]++;
    for (int i = 0, leaf = -1; i < n && (int)code.size() < n - 2; i++) {
        if (deg[i] != 1) continue;
        leaf = i;
        // 删去 leaf，若它的父亲因此变成编号更小的叶子，就继续删父亲（指针 i 不回退）
        while ((int)code.size() < n - 2) {
            int p = fa[leaf];
            code.push_back(p);
            deg[leaf] = 0;
            if (--deg[p] == 1 && p < i) leaf = p;
            else break;
        }
    }
    return code;
}

// 2. Prüfer 序列 → 树（返回以 n-1 为根的父亲数组），O(n)
vector<int> prufer_decode(const vector<int> &code) {
    int n = code.size() + 2;
    vector<int> deg(n, 1), fa(n, -1);
    for (int x : code) deg[x]++;
    int ptr = 0;
    while (deg[ptr] != 1) ptr++;
    int leaf = ptr;
    for (int x : code) {
        fa[leaf] = x;
        if (--deg[x] == 1 && x < ptr) leaf = x;   // x 变成了更小的叶子，下一步就删它
        else {
            ptr++;
            while (deg[ptr] != 1) ptr++;
            leaf = ptr;
        }
    }
    fa[leaf] = n - 1;   // 最后剩下 leaf 和 n-1
    return fa;
}
