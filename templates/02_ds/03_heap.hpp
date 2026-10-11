/**
 * 02_ds/03 堆与优先队列
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. priority_queue 与自定义比较
 *   2. 对顶堆：动态中位数
 *   3. 懒删除堆
 *   4. k 路归并
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/heap/
 *   OI-wiki        https://oi-wiki.org/ds/binary-heap/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/heap.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3378  P3378 【模板】堆
 *   https://www.luogu.com.cn/problem/P1168  P1168 中位数
 *   https://www.luogu.com.cn/problem/P1090  P1090 [NOIP 2004 提高组] 合并果子
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1190  普及−  P1190 [NOIP 2010 普及组] 接水问题  考点：模拟、搜索、贪心
 *   https://www.luogu.com.cn/problem/P1628  普及−  P1628 合并序列  考点：字符串、堆、排序
 *   https://www.luogu.com.cn/problem/P2369  普及−  P2369 EXCEEDED WARNING A  考点：堆
 *   https://www.luogu.com.cn/problem/P3887  普及−  P3887 [GDOI2014] 世界杯  考点：排序、优先队列、队列
 *   https://www.luogu.com.cn/problem/P9214  普及−  P9214 [入门赛 #11] 洛谷评测机模拟器 (Hard Version)  考点：堆、优先队列
 *   https://www.luogu.com.cn/problem/P1629  普及  P1629 邮递员送信  考点：图论、优先队列、最短路
 *   https://www.luogu.com.cn/problem/P1801  普及  P1801 黑匣子  考点：线段树、平衡树、堆
 *   https://www.luogu.com.cn/problem/P2058  普及  P2058 [NOIP 2016 普及组] 海港  考点：模拟、优先队列、队列
 *   https://www.luogu.com.cn/problem/P2085  普及  P2085 最小函数值  考点：数学、堆、排序
 *   https://www.luogu.com.cn/problem/P2859  普及  P2859 [USACO06FEB] Stall Reservations S  考点：贪心、线段树、优先队列
 *   https://codeforces.com/problemset/problem/1106/D  CF1500  CF1106D Lunar New Year and a Wander  考点：数据结构、搜索、图论
 *   https://codeforces.com/problemset/problem/1883/D  CF1500  CF1883D In Love  考点：数据结构、贪心
 *   https://codeforces.com/problemset/problem/1985/F  CF1500  CF1985F Final Boss  考点：二分、数据结构
 *   https://codeforces.com/problemset/problem/845/C  CF1500  CF845C Two TVs  考点：数据结构、贪心、排序
 *   https://codeforces.com/problemset/problem/1526/C2  CF1600  CF1526C2 Potions (Hard Version)  考点：数据结构、贪心
 *
 */

// 1. priority_queue 默认是大根堆
//    小根堆：priority_queue<ll, vector<ll>, greater<ll>> pq;
//    自定义：auto cmp = [](const T &a, const T &b) { return a.w > b.w; };  // 返回 true 表示 a 的优先级更低
//            priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);
//    pair 默认按 first、再按 second 比较；Dijkstra 常用 {距离, 点} 放入小根堆

// 2. 对顶堆：动态中位数。lo 是大根堆，存较小的一半；hi 是小根堆，存较大的一半
struct MedianHeap {
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<ll>> hi;
    void push(ll x) {
        if (lo.empty() || x <= lo.top()) lo.push(x);
        else hi.push(x);
        // 保持 lo.size() == hi.size() 或 lo.size() == hi.size() + 1
        if (lo.size() > hi.size() + 1) hi.push(lo.top()), lo.pop();
        else if (hi.size() > lo.size()) lo.push(hi.top()), hi.pop();
    }
    ll median() const { return lo.top(); }   // 个数为偶数时返回较小的那个中位数
    size_t size() const { return lo.size() + hi.size(); }
};

// 3. 懒删除堆：支持删除任意一个"确实在堆中"的元素
//    删除时先记到 del 里，等它到堆顶时再真正弹出
struct LazyHeap {
    priority_queue<ll> q, del;
    void push(ll x) { q.push(x); }
    void erase(ll x) { del.push(x); }
    void clean() {
        while (!del.empty() && q.top() == del.top()) q.pop(), del.pop();
    }
    ll top() { clean(); return q.top(); }
    void pop() { clean(); q.pop(); }
    size_t size() const { return q.size() - del.size(); }
    bool empty() const { return size() == 0; }
};

// 4. k 路归并：合并 k 个升序数组，O(N log k)
vector<ll> merge_k(const vector<vector<ll>> &lists) {
    using T = tuple<ll, int, int>;   // (值, 第几个数组, 数组中的下标)
    priority_queue<T, vector<T>, greater<T>> pq;
    for (int i = 0; i < (int)lists.size(); i++)
        if (!lists[i].empty()) pq.push({lists[i][0], i, 0});
    vector<ll> res;
    while (!pq.empty()) {
        auto [v, i, j] = pq.top();
        pq.pop();
        res.push_back(v);
        if (j + 1 < (int)lists[i].size()) pq.push({lists[i][j + 1], i, j + 1});
    }
    return res;
}
