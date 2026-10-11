/**
 * 01_basic/04 双指针与滑动窗口
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：01_basic/02 前缀和与差分
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 定长滑动窗口
 *   2. 不定长滑动窗口（同向双指针）
 *   3. 相向双指针
 *   4. 子数组计数（以右端点为准统计）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/two-pointer/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1638  P1638 逛画展
 *   https://www.luogu.com.cn/problem/P1102  P1102 A-B 数对
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P9950  入门  P9950 [USACO20FEB] Mad Scientist B  考点：双指针 two-pointer
 *   https://codeforces.com/problemset/problem/1462/A  CF800  CF1462A Favorite Sequence  考点：实现、双指针
 *   https://codeforces.com/problemset/problem/1791/C  CF800  CF1791C Prepend and Append  考点：实现、双指针
 *   https://codeforces.com/problemset/problem/381/A  CF800  CF381A Sereja and Dima  考点：贪心、实现、双指针
 *   https://www.luogu.com.cn/problem/P1094  普及−  P1094 [NOIP 2007 普及组] 纪念品分组  考点：贪心、排序、双指针 two-pointer
 *   https://www.luogu.com.cn/problem/P1296  普及−  P1296 奶牛的耳语  考点：模拟、二分、排序
 *   https://www.luogu.com.cn/problem/P15799  普及−  P15799 [GESP202603 五级] 找数  考点：二分、离散化、队列
 *   https://www.luogu.com.cn/problem/P2695  普及−  P2695 骑士的工作  考点：贪心、排序、双指针 two-pointer
 *   https://www.luogu.com.cn/problem/P10719  普及  P10719 [GESP202406 五级] 黑白格  考点：数学、二分、前缀和
 *   https://codeforces.com/problemset/problem/1692/E  CF1200  CF1692E Binary Deque  考点：二分、实现、双指针
 *   https://codeforces.com/problemset/problem/1793/C  CF1200  CF1793C Dora and Search  考点：构造、数据结构、双指针
 *   https://codeforces.com/problemset/problem/489/B  CF1200  CF489B BerSU Ball  考点：搜索、DP、图匹配
 *   https://codeforces.com/problemset/problem/279/B  CF1400  CF279B Books  考点：二分、暴力、实现
 *   https://codeforces.com/problemset/problem/550/B  CF1400  CF550B Preparing Olympiad  考点：位运算、暴力
 *   https://codeforces.com/problemset/problem/701/C  CF1500  CF701C They Are Everywhere  考点：二分、字符串、双指针
 *
 */

// 1. 定长滑动窗口：所有长度为 k 的子数组中的最大和（要求 1 <= k <= n）
ll max_window_sum(const vector<ll> &a, int k) {
    ll s = 0, best = LLONG_MIN;
    for (int i = 0; i < (int)a.size(); i++) {
        s += a[i];                     // 右端进入窗口
        if (i >= k) s -= a[i - k];     // 左端离开窗口
        if (i >= k - 1) best = max(best, s);
    }
    return best;
}

// 2. 不定长窗口求最长：最长的、元素互不相同的子数组长度
//    右端点每次右移一格；窗口不合法时右移左端点，直到重新合法
int longest_distinct(const vector<int> &a) {
    unordered_map<int, int> cnt;
    int ans = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        cnt[a[r]]++;
        while (cnt[a[r]] > 1) cnt[a[l++]]--;
        ans = max(ans, r - l + 1);
    }
    return ans;
}

// 3. 不定长窗口求最短：和 >= s 的最短子数组长度（元素为正数），不存在返回 -1
int shortest_sum_at_least(const vector<ll> &a, ll s) {
    int n = a.size(), ans = n + 1;
    ll sum = 0;
    for (int l = 0, r = 0; r < n; r++) {
        sum += a[r];
        while (sum - a[l] >= s && l < r) sum -= a[l++];   // 尽量缩短
        if (sum >= s) ans = min(ans, r - l + 1);
    }
    return ans > n ? -1 : ans;
}

// 4. 子数组计数：和 <= s 的子数组个数（元素非负）。以 r 为右端点的合法子数组有 r - l + 1 个
ll count_sum_at_most(const vector<ll> &a, ll s) {
    ll sum = 0, ans = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (l <= r && sum > s) sum -= a[l++];
        ans += r - l + 1;
    }
    return ans;
}

// 5. 相向双指针：在升序数组中找和为 t 的两个下标 i < j，不存在返回 {-1, -1}
pair<int, int> two_sum_sorted(const vector<ll> &a, ll t) {
    int i = 0, j = (int)a.size() - 1;
    while (i < j) {
        ll s = a[i] + a[j];
        if (s == t) return {i, j};
        if (s < t) i++;
        else j--;
    }
    return {-1, -1};
}
