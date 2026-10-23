/**
 * 05_math/13 博弈论
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：01_basic/06 位运算
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. Nim 游戏
 *   2. SG 函数与 SG 定理
 *   3. 常见博弈模型（巴什、威佐夫）
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/game-theory/impartial-game/
 *   cp-algorithms  https://cp-algorithms.com/game_theory/sprague-grundy-nim.html
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/games.go
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P2197  P2197 【模板】Nim 游戏
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P2148  提高  P2148 [SDOI2009] E&D  考点：博弈论、枚举、位运算
 *   https://www.luogu.com.cn/problem/P3480  提高  P3480 [POI 2009] KAM-Pebbles  考点：博弈论
 *   https://www.luogu.com.cn/problem/P4101  提高  P4101 [HEOI2014] 人人尽说江南好  考点：博弈论
 *   https://www.luogu.com.cn/problem/P4279  提高  P4279 [SHOI2008] 小约翰的游戏  考点：博弈论、SG 函数
 *   https://codeforces.com/problemset/problem/1728/D  CF1800  CF1728D Letter Picking  考点：构造、DP、博弈
 *   https://codeforces.com/problemset/problem/15/C  CF2000  CF15C Industrial Nim  考点：博弈
 *   https://codeforces.com/problemset/problem/1903/E  CF2000  CF1903E Geo Game  考点：贪心、交互、数学
 *   https://codeforces.com/problemset/problem/78/C  CF2000  CF78C Beaver Game  考点：DP、博弈、数论
 *   https://codeforces.com/problemset/problem/936/B  CF2100  CF936B Sleepy Game  考点：搜索、DP、博弈
 *   https://codeforces.com/problemset/problem/850/C  CF2200  CF850C Arpa and a game with Mojtaba  考点：位运算、DP、博弈
 *   https://codeforces.com/problemset/problem/1934/D2  CF2400  CF1934D2 XOR Break --- Game Version  考点：位运算、博弈、贪心
 *   https://www.luogu.com.cn/problem/P2252  省选/NOI−  P2252 【模板】威佐夫博弈 / [SHOI2002] 取石子游戏  考点：数学、博弈论
 *   https://www.luogu.com.cn/problem/P5363  省选/NOI−  P5363 [SDOI2019] 移动金币  考点：动态规划 DP、博弈论
 *   https://codeforces.com/problemset/problem/1312/F  CF2500  CF1312F Attack on Red Kingdom  考点：博弈、双指针
 *   https://codeforces.com/problemset/problem/1823/E  CF2500  CF1823E Removing Graph  考点：暴力、DP、博弈
 *
 */

// 公平组合游戏：两人轮流操作、可选操作只与局面有关、不能操作的人输。
// 必胜态：存在一步能走到必败态；必败态：所有操作都走到必胜态。

// 1. Nim 游戏：若干堆石子，每次从一堆中取任意个。先手必胜 ⇔ 各堆数量的异或和不为 0
bool nim_first_wins(const vector<ll> &a) {
    ll x = 0;
    for (ll v : a) x ^= v;
    return x != 0;
}

// 2. SG 函数：SG(x) = mex{ SG(y) : x 能一步走到 y }，mex 为不在集合中的最小非负整数。
//    SG(x) = 0 ⇔ x 是必败态。SG 定理：多个游戏的和，SG 值为各自 SG 值的异或。
int mex(vector<int> s) {
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    int m = 0;
    for (int v : s) {
        if (v != m) break;
        m++;
    }
    return m;
}
//    例：一堆石子，每次可以取 S 中的某个数量。返回 SG(0..N)
vector<int> sg_subtraction(int N, const vector<int> &S) {
    vector<int> sg(N + 1, 0);
    for (int x = 1; x <= N; x++) {
        vector<int> nxt;
        for (int s : S)
            if (s <= x) nxt.push_back(sg[x - s]);
        sg[x] = mex(nxt);
    }
    return sg;
}

// 3. 巴什博弈：一堆 n 个，每次取 1..m 个。先手必败 ⇔ n % (m + 1) == 0
bool bash_first_wins(ll n, ll m) { return n % (m + 1) != 0; }

// 4. 威佐夫博弈：两堆 (a, b)，每次从一堆取任意个，或从两堆取相同个数。
//    设 a <= b，先手必败 ⇔ a == floor((b - a) · (1 + √5) / 2)。数很大（> 1e15）时注意精度
bool wythoff_first_wins(ll a, ll b) {
    if (a > b) swap(a, b);
    long double phi = (1 + sqrtl(5.0L)) / 2;
    return a != (ll)floorl((b - a) * phi);
}
