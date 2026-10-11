/**
 * 07_string/05 最小表示法
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 循环同构串的最小表示
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/minimal-string/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/strings.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1368  P1368 工艺
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://codeforces.com/problemset/problem/496/B  CF1500  CF496B Secret Combination  枚举加法次数 + 最小循环同构
 *   https://www.luogu.com.cn/problem/P13270  提高  P13270 【模板】最小表示法  最小表示法模板
 *   https://www.luogu.com.cn/problem/P1709  提高  P1709 [SEERC 2003 / USACO5.5] 隐藏口令 Hidden Password  最小表示法直接应用
 *   https://codeforces.com/problemset/problem/1017/E  CF2400  CF1017E The Supersonic Rocket  把凸包编码成字符串，判循环同构
 *   https://www.luogu.com.cn/problem/P6114  省选/NOI−  P6114 【模板】Lyndon 分解  Lyndon 分解：最小表示法的理论延伸
 *   https://www.luogu.com.cn/problem/P5334  NOI/NOI+/CTS  P5334 [JSOI2019] 节日庆典  每个前缀的最小循环表示（Lyndon）
 *
 */

// 最小表示法：字符串 s 的所有循环同构串（把开头若干个字符移到末尾）中字典序最小的那个（洛谷 P1368）。
// 双指针 i、j 表示两个候选起点，k 为当前已匹配的长度。若 s[i+k] > s[j+k]，
// 则以 i, i+1, ..., i+k 开头的都不可能是最小的，i 直接跳到 i+k+1（j 同理）。O(n)
// 返回最小循环同构串的起始下标（有多个时返回最小的下标）
int min_rotation(const string &s) {
    int n = s.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        char a = s[(i + k) % n], b = s[(j + k) % n];
        if (a == b) { k++; continue; }
        if (a > b) i += k + 1;
        else j += k + 1;
        if (i == j) j++;
        k = 0;
    }
    return min(i, j);
}
// 最小表示：s.substr(p) + s.substr(0, p)，其中 p = min_rotation(s)
