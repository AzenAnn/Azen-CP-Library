/**
 * 02_ds/02 单调队列
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：02_ds/01 栈与单调栈
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 滑动窗口最大 / 最小值
 *   2. deque 的使用
 *   3. 单调队列优化 DP（见 06_dp/08）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/monotonous-queue/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/monotone_queue.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1886  P1886 【模板】单调队列 / 滑动窗口
 *   https://www.luogu.com.cn/problem/P2032  P2032 扫描
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1203  普及−  P1203 [IOI 1993 / USACO1.1] 坏掉的项链 Broken Necklace  考点：字符串、动态规划 DP、搜索
 *   https://www.luogu.com.cn/problem/P15097  普及−  P15097 [ICPC 2025 LAC] Coatless in Yakutsk  考点：贪心、二分、并查集
 *   https://www.luogu.com.cn/problem/P11963  普及  P11963 [GESP202503 六级] 环线  考点：动态规划 DP、单调队列、前缀和
 *   https://www.luogu.com.cn/problem/P1440  普及  P1440 求m区间内的最小值  考点：单调队列、队列、ST 表
 *   https://www.luogu.com.cn/problem/P1714  普及  P1714 切蛋糕  考点：线段树、树状数组、单调队列
 *   https://www.luogu.com.cn/problem/P2251  普及  P2251 质量检测  考点：单调队列、ST 表
 *   https://www.luogu.com.cn/problem/P2629  普及  P2629 好消息，坏消息  考点：线性数据结构、单调队列、前缀和
 *   https://www.luogu.com.cn/problem/P4085  普及  P4085 [USACO17DEC] Haybale Feast G  考点：线段树、二分、单调队列
 *   https://codeforces.com/problemset/problem/1736/C1  CF1300  CF1736C1 Good Subarrays (Easy Version)  考点：二分、数据结构、调度
 *   https://www.luogu.com.cn/problem/P1419  普及+/提高−  P1419 寻找段落  考点：二分、单调队列
 *   https://www.luogu.com.cn/problem/P2216  普及+/提高−  P2216 [HAOI2007] 理想的正方形  考点：单调队列、队列、ST 表
 *   https://www.luogu.com.cn/problem/P3572  普及+/提高−  P3572 [POI 2014] PTA-Little Bird  考点：动态规划 DP、单调队列
 *   https://www.luogu.com.cn/problem/P3800  普及+/提高−  P3800 Power 收集  考点：动态规划 DP、单调队列、ST 表
 *   https://codeforces.com/problemset/problem/1898/B  CF1500  CF1898B Milena and Admirer  考点：贪心、数学
 *   https://codeforces.com/problemset/problem/1941/E  CF1600  CF1941E Rudolf and k Bridges  考点：二分、数据结构、DP
 *
 */

// 1. 所有长度为 k 的窗口的最大值（共 n - k + 1 个）。求最小值把 <= 改成 >=
//    队列中存下标，对应的值从队头到队尾严格递减；队头就是当前窗口的最大值
vector<ll> window_max(const vector<ll> &a, int k) {
    deque<int> q;
    vector<ll> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();   // 比 a[i] 小的永远不会再成为最大值
        q.push_back(i);
        if (q.front() <= i - k) q.pop_front();                     // 队头离开窗口
        if (i >= k - 1) res.push_back(a[q.front()]);
    }
    return res;
}

// 2. 支持随时取最大值的队列：队尾加入、队头弹出，窗口长度可以不固定
struct MaxQueue {
    deque<pair<ll, int>> q;   // (值, 入队编号)
    int head = 0, tail = 0;   // 已弹出的个数、已加入的个数
    void push(ll x) {
        while (!q.empty() && q.back().first <= x) q.pop_back();
        q.push_back({x, tail++});
    }
    void pop() {              // 弹出最早加入的元素（队列须非空）
        if (q.front().second == head) q.pop_front();
        head++;
    }
    ll max() const { return q.front().first; }
    int size() const { return tail - head; }
};
