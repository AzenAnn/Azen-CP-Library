/**
 * 02_ds/01 栈与单调栈
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 栈：括号匹配、表达式
 *   2. 单调栈：下一个更大 / 更小元素
 *   3. 以 a[i] 为最值的最大区间（贡献法）
 *   4. 柱状图中最大矩形
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/ds/stack/
 *   OI-wiki        https://oi-wiki.org/ds/monotonous-stack/
 *   cp-algorithms  https://cp-algorithms.com/data_structures/stack_queue_modification.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/monotone_stack.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5788  P5788 【模板】单调栈
 *   https://www.luogu.com.cn/problem/P2866  P2866 [USACO06NOV] Bad Hair Day S
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1427  入门  P1427 小鱼的数字游戏  考点：栈
 *   https://www.luogu.com.cn/problem/P14325  入门  P14325 [JOI2022 预选赛 R2] 图书馆 2 / Library 2  考点：模拟、栈
 *   https://www.luogu.com.cn/problem/P1739  入门  P1739 表达式括号匹配  考点：模拟、字符串、线性数据结构
 *   https://www.luogu.com.cn/problem/P1044  普及−  P1044 [NOIP 2003 普及组] 栈  考点：动态规划 DP、数学、递推
 *   https://www.luogu.com.cn/problem/P1165  普及−  P1165 日志分析  考点：模拟、线性数据结构、堆
 *   https://www.luogu.com.cn/problem/P1449  普及−  P1449 后缀表达式  考点：模拟、字符串、线性数据结构
 *   https://www.luogu.com.cn/problem/P1981  普及−  P1981 [NOIP 2013 普及组] 表达式求值  考点：模拟、字符串、栈
 *   https://www.luogu.com.cn/problem/P1901  普及  P1901 发射站  考点：栈、单调栈
 *   https://www.luogu.com.cn/problem/P4387  普及  P4387 【深基15.习9】验证栈序列  考点：模拟、栈
 *   https://codeforces.com/problemset/problem/1076/A  CF1200  CF1076A Minimizing the String  考点：贪心、字符串
 *   https://codeforces.com/problemset/problem/1730/C  CF1200  CF1730C Minimum Notation  考点：数据结构、贪心、数学
 *   https://codeforces.com/problemset/problem/1905/C  CF1400  CF1905C Largest Subsequence  考点：贪心、字符串
 *   https://codeforces.com/problemset/problem/91/B  CF1500  CF91B Queue  考点：二分、数据结构
 *   https://codeforces.com/problemset/problem/1886/C  CF1600  CF1886C Decreasing String  考点：实现、字符串
 *   https://codeforces.com/problemset/problem/2046/B  CF1600  CF2046B Move Back at a Cost  考点：二分、数据结构、贪心
 *
 */

// 栈中存下标。求"更大"时，栈中下标对应的值从栈底到栈顶严格递减；
// 求"更小"只需把比较符号反过来。每个下标最多进出栈一次，总复杂度 O(n)。

// 1. 每个 i 左边最近的、严格大于 a[i] 的下标，不存在为 -1
vector<int> left_greater(const vector<ll> &a) {
    int n = a.size();
    vector<int> res(n), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        res[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    return res;
}

// 2. 每个 i 右边最近的、严格大于 a[i] 的下标，不存在为 n
vector<int> right_greater(const vector<ll> &a) {
    int n = a.size();
    vector<int> res(n), st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        res[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    return res;
}

// 3. 贡献法：所有子数组最小值之和。
//    a[i] 是子数组 (L, R) 的最小值，其中 L = 左边最近的 < a[i]，R = 右边最近的 <= a[i]。
//    一边严格、一边不严格，保证有相等元素时每个子数组只被算一次。
ll sum_subarray_min(const vector<ll> &a) {
    int n = a.size();
    vector<int> L(n), R(n), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        L[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        R[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += a[i] * (i - L[i]) * (R[i] - i);
    return ans;
}

// 4. 柱状图中最大矩形：以 h[i] 为高的矩形，向左右延伸到第一个更矮的柱子为止
ll largest_rectangle(const vector<ll> &h) {
    int n = h.size();
    vector<int> st;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ll cur = i < n ? h[i] : -1;   // 末尾放一个哨兵，把栈清空
        while (!st.empty() && h[st.back()] >= cur) {
            ll height = h[st.back()];
            st.pop_back();
            int left = st.empty() ? -1 : st.back();
            ans = max(ans, height * (i - left - 1));
        }
        st.push_back(i);
    }
    return ans;
}
