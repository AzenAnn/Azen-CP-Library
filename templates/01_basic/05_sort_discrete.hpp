/**
 * 01_basic/05 排序与离散化
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. sort 与自定义比较（严格弱序）
 *   2. 归并排序求逆序对
 *   3. nth_element 求第 k 小
 *   4. 离散化（排序 + 去重 + 二分）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/basic/sort-intro/
 *   OI-wiki        https://oi-wiki.org/basic/merge-sort/
 *   OI-wiki        https://oi-wiki.org/misc/discrete/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/sort.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1908  P1908 逆序对
 *   https://www.luogu.com.cn/problem/P1923  P1923 【深基9.例4】求第 k 小的数
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1152  入门  P1152 欢乐的跳  考点：模拟、枚举、排序
 *   https://www.luogu.com.cn/problem/P1888  入门  P1888 三角函数  考点：数学、排序、最大公约数 gcd
 *   https://www.luogu.com.cn/problem/P4414  入门  P4414 [COCI 2006/2007 #2] ABC  考点：模拟、排序
 *   https://codeforces.com/problemset/problem/339/A  CF800  CF339A Helpful Maths  考点：贪心、实现、排序
 *   https://www.luogu.com.cn/problem/P1059  普及−  P1059 [NOIP 2006 普及组] 明明的随机数  考点：模拟、排序、STL
 *   https://www.luogu.com.cn/problem/P1093  普及−  P1093 [NOIP 2007 普及组] 奖学金  考点：模拟、数学、排序
 *   https://www.luogu.com.cn/problem/P1177  普及−  P1177 【模板】排序  考点：排序
 *   https://www.luogu.com.cn/problem/P1223  普及−  P1223 排队接水  考点：贪心、排序
 *   https://www.luogu.com.cn/problem/P1056  普及  P1056 [NOIP 2008 普及组] 排座椅  考点：贪心、排序
 *   https://www.luogu.com.cn/problem/P1111  普及  P1111 修复公路  考点：二分、并查集、排序
 *   https://www.luogu.com.cn/problem/P7910  普及  P7910 [CSP-J 2021] 插入排序  考点：枚举、排序
 *   https://codeforces.com/problemset/problem/977/C  CF1200  CF977C Less or Equal  考点：排序
 *   https://www.luogu.com.cn/problem/P1012  普及+/提高−  P1012 [NOIP 1998 提高组] 拼数  考点：字符串、贪心、排序
 *   https://www.luogu.com.cn/problem/P1020  普及+/提高−  P1020 [NOIP 1999 提高组] 导弹拦截  考点：动态规划 DP、贪心、线段树
 *   https://www.luogu.com.cn/problem/P1525  普及+/提高−  P1525 [NOIP 2010 提高组] 关押罪犯  考点：图论、贪心、二分
 *
 */

// 1. 自定义比较必须是"严格弱序"：用 <，不能用 <=，否则 sort 可能越界 RE
//    sort(a.begin(), a.end(), [](const auto &x, const auto &y) { return x.second < y.second; });
//    需要稳定排序（相等元素保持原顺序）用 stable_sort

// 2. 归并排序求逆序对个数，O(n log n)。区间左闭右开 [l, r)
ll merge_count(vector<ll> &a, vector<ll> &tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    ll res = merge_count(a, tmp, l, m) + merge_count(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) tmp[k++] = a[i++];
        else res += m - i, tmp[k++] = a[j++];   // a[i..m) 都比 a[j] 大
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return res;
}
ll inversions(vector<ll> a) {
    vector<ll> tmp(a.size());
    return merge_count(a, tmp, 0, a.size());
}

// 3. 第 k 小（k 从 0 开始），平均 O(n)：
//    nth_element(a.begin(), a.begin() + k, a.end());  之后 a[k] 就是第 k 小

// 4. 离散化：把值映射到 0..m-1，保持大小关系
struct Discrete {
    vector<ll> v;
    Discrete(vector<ll> a) : v(move(a)) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    int id(ll x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); }  // x 须出现过
    ll value(int i) const { return v[i]; }
    int size() const { return v.size(); }
};
