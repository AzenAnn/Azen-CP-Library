/**
 * 06_dp/12 插头 DP（轮廓线 DP）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：06_dp/06 状压 DP
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 轮廓线：逐格转移，记录当前格与上方/左方的连通状态（插头）
 *   2. 括号表示法：每格两状态（无插头/左括号/右括号），用三进制或四进制
 *   3. 最小表示法：对连通块标号，哈希存状态
 *   4. 经典模型：多回路覆盖、单回路（哈密顿）、连通块计数
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/dp/plug/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5056  P5056 【模板】插头 DP
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3886  省选/NOI−  P3886 [JLOI2009] 神秘的生物  考点：轮廓线 DP、动态规划 DP、进制
 *   https://www.luogu.com.cn/problem/P4262  省选/NOI−  P4262 [Code+#3] 白金元首与莫斯科  考点：轮廓线 DP
 *   https://www.luogu.com.cn/problem/P5074  省选/NOI−  P5074 Eat the Trees  考点：多回路：不需要括号匹配，插头只记有无
 *   https://www.luogu.com.cn/problem/P1713  NOI/NOI+/CTS  P1713 麦当劳叔叔的难题  考点：轮廓线 DP
 *   https://www.luogu.com.cn/problem/P1933  NOI/NOI+/CTS  P1933 [NOI2010] 旅行路线  考点：轮廓线 DP、动态规划 DP、剪枝
 *   https://www.luogu.com.cn/problem/P2289  NOI/NOI+/CTS  P2289 [HNOI2004] 邮递员  考点：轮廓线 DP、动态规划 DP、高精度
 *   https://www.luogu.com.cn/problem/P2337  NOI/NOI+/CTS  P2337 [SCOI2012] 喵星人的入侵  考点：轮廓线 DP、构造
 *   https://www.luogu.com.cn/problem/P3190  NOI/NOI+/CTS  P3190 [HNOI2007] 神奇游乐园  考点：轮廓线 DP、动态规划 DP
 *   https://www.luogu.com.cn/problem/P3272  NOI/NOI+/CTS  P3272 [SCOI2011] 地板  考点：轮廓线 DP、动态规划 DP、广度优先搜索 BFS
 *
 */

// 插头 DP（括号表示法）：网格中有障碍，求恰好经过所有空格一次的回路（哈密顿回路）个数（【模板】插头 DP）。
// 逐格转移，轮廓线上 m+1 个位置各存一个插头：0 无，1 左括号（回路的一段的起点），2 右括号（终点）。
// 处理格子 (i, j) 时，位置 j 是左边伸过来的插头，位置 j+1 是上面伸下来的插头；处理完后它们分别变成向下、向右的插头。
// 状态用 4 进制压在 ull 里（m ≤ 31），用哈希表滚动。只有在最后一个空格才允许把 1、2 两个插头接成一个回路。
ll count_hamiltonian_cycles(const vector<string> &grid) {
    int n = grid.size(), m = n ? grid[0].size() : 0;
    int ex = -1, ey = -1;   // 最后一个空格
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '.') ex = i, ey = j;
    if (ex < 0) return 0;
    auto get = [](unsigned long long s, int p) { return (int)(s >> (2 * p) & 3); };
    auto put = [](unsigned long long s, int p, unsigned long long v) { return (s & ~(3ULL << (2 * p))) | (v << (2 * p)); };
    auto free_cell = [&](int i, int j) { return i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '.'; };
    unordered_map<unsigned long long, ll> cur = {{0, 1}}, nxt;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        nxt.clear();   // 换行：最右边的插头必须为空，整体左移一位
        for (auto [s, c] : cur)
            if (get(s, m) == 0) nxt[s << 2] += c;
        swap(cur, nxt);
        for (int j = 0; j < m; j++) {
            nxt.clear();
            for (auto [s, c] : cur) {
                int b1 = get(s, j), b2 = get(s, j + 1);
                auto add = [&](unsigned long long t) { nxt[t] += c; };
                if (!free_cell(i, j)) {
                    if (!b1 && !b2) add(s);
                    continue;
                }
                bool down = free_cell(i + 1, j), right = free_cell(i, j + 1);
                if (!b1 && !b2) {   // 新建一对插头：向下为左括号，向右为右括号
                    if (down && right) add(put(put(s, j, 1), j + 1, 2));
                } else if (!b1 || !b2) {   // 只有一个插头：向下或向右延伸
                    int b = b1 | b2;
                    if (down) add(put(put(s, j, b), j + 1, 0));
                    if (right) add(put(put(s, j, 0), j + 1, b));
                } else {
                    unsigned long long t = put(put(s, j, 0), j + 1, 0);
                    if (b1 == 1 && b2 == 1) {   // 两个左括号：把 b2 匹配的右括号改成左括号
                        for (int p = j + 2, d = 1;; p++) {
                            int x = get(t, p);
                            d += x == 1 ? 1 : x == 2 ? -1 : 0;
                            if (d == 0) { add(put(t, p, 1)); break; }
                        }
                    } else if (b1 == 2 && b2 == 2) {   // 两个右括号：把 b1 匹配的左括号改成右括号
                        for (int p = j - 1, d = 1;; p--) {
                            int x = get(t, p);
                            d += x == 2 ? 1 : x == 1 ? -1 : 0;
                            if (d == 0) { add(put(t, p, 2)); break; }
                        }
                    } else if (b1 == 2 && b2 == 1) {
                        add(t);   // 两段连起来
                    } else if (i == ex && j == ey) {
                        ans += c;   // b1 = 1, b2 = 2：闭合成回路，只能在最后一个空格
                    }
                }
            }
            swap(cur, nxt);
        }
    }
    return ans;
}
