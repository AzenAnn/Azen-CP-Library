/**
 * 01_basic/08 高精度
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 高精度加减
 *   2. 高精度乘低精度
 *   3. 高精度乘高精度
 *   4. 高精度除以低精度
 *   5. 能用 __int128 时优先用 __int128
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/bignum/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/big.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1601  P1601 高精度加法
 *   https://www.luogu.com.cn/problem/P1303  P1303 A*B Problem
 *   https://www.luogu.com.cn/problem/P1480  P1480 A/B Problem（高精度除法Ⅰ）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1009  普及−  P1009 [NOIP 1998 普及组] 阶乘之和  考点：数学、高精度
 *   https://www.luogu.com.cn/problem/P1015  普及−  P1015 [NOIP 1999 普及组] 回文数  考点：模拟、高精度、进制
 *   https://www.luogu.com.cn/problem/P1255  普及−  P1255 数楼梯  考点：高精度、递推、Fibonacci 数列
 *   https://www.luogu.com.cn/problem/P1781  普及−  P1781 宇宙总统  考点：字符串、高精度、排序
 *   https://www.luogu.com.cn/problem/P2142  普及−  P2142 高精度减法  考点：模拟、高精度
 *   https://www.luogu.com.cn/problem/P1037  普及  P1037 [NOIP 2002 普及组] 产生数  考点：搜索、图论、高精度
 *   https://www.luogu.com.cn/problem/P1045  普及  P1045 [NOIP 2003 普及组] 麦森数  考点：数学、高精度
 *   https://www.luogu.com.cn/problem/P1096  普及  P1096 [NOIP 2007 普及组] Hanoi 双塔问题  考点：数学、高精度、递推
 *   https://www.luogu.com.cn/problem/P1249  普及  P1249 最大乘积  考点：贪心、高精度
 *   https://www.luogu.com.cn/problem/P2005  普及  P2005 A/B Problem II  考点：高精度、二分
 *   https://www.luogu.com.cn/problem/P1005  普及+/提高−  P1005 [NOIP 2007 提高组] 矩阵取数游戏  考点：动态规划 DP、高精度、区间 DP
 *   https://www.luogu.com.cn/problem/P1018  普及+/提高−  P1018 [NOIP 2000 提高组] 乘积最大  考点：动态规划 DP、搜索、高精度
 *   https://www.luogu.com.cn/problem/P1932  普及+/提高−  P1932 A+B  A-B  A*B  A/B A%B Problem  考点：数学、高精度
 *   https://www.luogu.com.cn/problem/P1982  普及+/提高−  P1982 [NOIP 2013 普及组] 小朋友的数字  考点：动态规划 DP、高精度、递推
 *   https://codeforces.com/problemset/problem/1181/B  CF1500  CF1181B Split a Number  考点：贪心、实现、字符串
 *
 */

// 高精度非负整数：vector<int> 逆序存放每一位，d[0] 是个位。0 表示为 {0}
// 能用 __int128（约 1.7e38）解决的题优先用 __int128
using Big = vector<int>;

void big_trim(Big &a) {   // 去掉高位多余的 0
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}
Big big_from(const string &s) {
    Big a;
    for (int i = (int)s.size() - 1; i >= 0; i--) a.push_back(s[i] - '0');
    if (a.empty()) a.push_back(0);
    big_trim(a);
    return a;
}
string big_str(const Big &a) {
    string s;
    for (int i = (int)a.size() - 1; i >= 0; i--) s += char('0' + a[i]);
    return s;
}
int big_cmp(const Big &a, const Big &b) {   // a < b 返回 -1，相等返回 0，a > b 返回 1
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = (int)a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    return 0;
}

// 1. 加法：逐位相加，处理进位
Big big_add(const Big &a, const Big &b) {
    Big c;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; i++) {
        int s = carry + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
        c.push_back(s % 10), carry = s / 10;
    }
    return c;
}

//    减法：要求 a >= b，逐位相减，处理借位。a < b 时算 b - a 再加负号
Big big_sub(const Big &a, const Big &b) {
    Big c;
    int borrow = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int s = a[i] - borrow - (i < b.size() ? b[i] : 0);
        borrow = s < 0;
        c.push_back(s + borrow * 10);
    }
    big_trim(c);
    return c;
}

// 2. 高精度乘低精度：b 为非负整数，b <= 1e17
Big big_mul_small(const Big &a, ll b) {
    Big c;
    ll carry = 0;
    for (size_t i = 0; i < a.size() || carry; i++) {
        ll s = carry + (i < a.size() ? a[i] * b : 0);
        c.push_back(s % 10), carry = s / 10;
    }
    big_trim(c);
    return c;
}

// 3. 高精度乘高精度：c[i + j] += a[i] * b[j]，最后统一进位，O(nm)
Big big_mul(const Big &a, const Big &b) {
    vector<ll> t(a.size() + b.size(), 0);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < b.size(); j++) t[i + j] += a[i] * b[j];
    Big c;
    ll carry = 0;
    for (size_t i = 0; i < t.size(); i++) {
        ll s = t[i] + carry;
        c.push_back(s % 10), carry = s / 10;
    }
    big_trim(c);
    return c;
}

// 4. 高精度除以低精度：从最高位开始模拟竖式除法，返回 {商, 余数}，要求 1 <= b <= 1e17
pair<Big, ll> big_divmod_small(const Big &a, ll b) {
    Big q(a.size());
    ll r = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        r = r * 10 + a[i];
        q[i] = r / b, r %= b;
    }
    big_trim(q);
    return {q, r};
}

//    高精度除以高精度：竖式除法，每一位用减法试商（最多减 9 次），O(n^2)。要求 b != 0
pair<Big, Big> big_divmod(const Big &a, const Big &b) {
    Big q(a.size(), 0), r{0};
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        r.insert(r.begin(), a[i]);   // r = r * 10 + a[i]
        big_trim(r);
        while (big_cmp(r, b) >= 0) r = big_sub(r, b), q[i]++;
    }
    big_trim(q);
    return {q, r};
}
