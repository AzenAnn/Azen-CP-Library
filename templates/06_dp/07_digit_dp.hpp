/**
 * 06_dp/07 数位 DP
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：06_dp/01 线性 DP 入门与记忆化搜索
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 记忆化搜索模板（limit、前导零）
 *   2. 按位统计计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/number/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/dp.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2602  P2602 [ZJOI2010] 数字计数
 *   https://www.luogu.com.cn/problem/P2657  P2657 [SCOI2009] windy 数
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2188  提高  P2188 小Z的 k 紧凑数  考点：动态规划 DP、数位 DP
 *   https://www.luogu.com.cn/problem/P4124  提高  P4124 [CQOI2016] 手机号码  考点：动态规划 DP、数位 DP
 *   https://www.luogu.com.cn/problem/P4127  提高  P4127 [AHOI2009] 同类分布  考点：动态规划 DP、搜索、递推
 *   https://www.luogu.com.cn/problem/P4317  提高  P4317 花神的数论题  考点：枚举、数位 DP、进制
 *   https://codeforces.com/problemset/problem/1036/C  CF1900  CF1036C Classy Numbers  考点：组合数学、DP
 *   https://www.luogu.com.cn/problem/P3193  提高+/省选−  P3193 [HNOI2008] GT考试  考点：动态规划 DP、递推、矩阵加速
 *   https://codeforces.com/problemset/problem/431/D  CF2100  CF431D Random Task  考点：二分、位运算、组合数学
 *   https://codeforces.com/problemset/problem/628/D  CF2200  CF628D Magic Numbers  考点：DP
 *   https://codeforces.com/problemset/problem/1073/E  CF2300  CF1073E Segment Sum  考点：位运算、组合数学、DP
 *   https://codeforces.com/problemset/problem/1245/F  CF2300  CF1245F Daniel and Spring Cleaning  考点：位运算、暴力、组合数学
 *   https://codeforces.com/problemset/problem/1670/F  CF2400  CF1670F Jee, You See?  考点：位运算、组合数学、DP
 *   https://www.luogu.com.cn/problem/P6669  省选/NOI−  P6669 [清华集训 2016] 组合数问题  考点：数位 DP、Lucas 定理
 *   https://www.luogu.com.cn/problem/P8688  省选/NOI−  P8688 [蓝桥杯 2019 省 A] 组合数问题  考点：数位 DP、Lucas 定理
 *   https://codeforces.com/problemset/problem/1710/C  CF2500  CF1710C XOR Triangle  考点：位运算、暴力、构造
 *   https://codeforces.com/problemset/problem/55/D  CF2500  CF55D Beautiful numbers  考点：DP、数论
 *
 */

// 数位 DP：统计 [0, N] 或 [1, N] 中满足某种条件的数。把 N 拆成十进制数位，从高位往低位逐位填数。
// 记忆化搜索的通用参数：
//   pos   当前填到第几位
//   limit 前面每一位是否都和 N 相同（是的话这一位最多填 N 的这一位，否则可以填 0..9）
//   lead  前面是否都是前导零（影响"数字 0 算不算出现"、"相邻数字之差"等）
//   以及题目需要的状态（如上一位填了什么、某个数字出现了几次）
// 只有 limit = false 且 lead = false 的状态才能记忆化（其他状态只会访问一次）。
// 区间 [a, b] 的答案 = f(b) - f(a - 1)

// 1. [1, N] 中每个数字 0..9 一共出现了多少次（洛谷 P2602）
array<ll, 10> digit_count(ll N) {
    array<ll, 10> res{};
    if (N <= 0) return res;
    string s = to_string(N);
    int L = s.size();
    for (int d = 0; d <= 9; d++) {
        vector<vector<ll>> memo(L, vector<ll>(L + 1, -1));   // memo[pos][cnt]
        function<ll(int, int, bool, bool)> dfs = [&](int pos, int cnt, bool limit, bool lead) -> ll {
            if (pos == L) return lead ? 0 : cnt;   // 全是前导零表示数字 0，不计入
            if (!limit && !lead && memo[pos][cnt] != -1) return memo[pos][cnt];
            ll r = 0;
            int up = limit ? s[pos] - '0' : 9;
            for (int x = 0; x <= up; x++) {
                bool nlead = lead && x == 0;
                r += dfs(pos + 1, cnt + (x == d && !nlead), limit && x == up, nlead);
            }
            if (!limit && !lead) memo[pos][cnt] = r;
            return r;
        };
        res[d] = dfs(0, 0, true, true);
    }
    return res;
}

// 2. windy 数（洛谷 P2657）：不含前导零、且相邻两个数字之差至少为 2 的正整数，求 [1, N] 中的个数
ll windy_count(ll N) {
    if (N <= 0) return 0;
    string s = to_string(N);
    int L = s.size();
    vector<vector<ll>> memo(L, vector<ll>(10, -1));   // memo[pos][上一位]
    function<ll(int, int, bool, bool)> dfs = [&](int pos, int last, bool limit, bool lead) -> ll {
        if (pos == L) return lead ? 0 : 1;
        if (!limit && !lead && memo[pos][last] != -1) return memo[pos][last];
        ll r = 0;
        int up = limit ? s[pos] - '0' : 9;
        for (int x = 0; x <= up; x++) {
            if (!lead && abs(x - last) < 2) continue;
            r += dfs(pos + 1, x, limit && x == up, lead && x == 0);
        }
        if (!limit && !lead) memo[pos][last] = r;
        return r;
    };
    return dfs(0, 0, true, true);
}
