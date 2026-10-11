/**
 * 09_misc/03 模拟退火
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：09_misc/01 随机数与防卡哈希
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 温度、降温系数与接受概率
 *   2. 卡时技巧
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/misc/simulated-annealing/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P1337  P1337 [JSOI2004] 平衡点 / 吊打XXX
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P14148  提高  P14148 错觉  考点：模拟退火、随机化、构造
 *   https://www.luogu.com.cn/problem/P1559  提高  P1559 运动员最佳匹配问题  考点：搜索、剪枝、模拟退火
 *   https://www.luogu.com.cn/problem/P2503  提高  P2503 [HAOI2006] 均分数据  考点：模拟、贪心、模拟退火
 *   https://www.luogu.com.cn/problem/P3475  提高  P3475 [POI 2008] POD-Subdivision of Kingdom  考点：枚举、深度优先搜索 DFS、模拟退火
 *   https://www.luogu.com.cn/problem/P3878  提高  P3878 [TJOI2010] 分金币  考点：模拟退火、进制、折半搜索 meet in the middle
 *   https://www.luogu.com.cn/problem/P4035  提高  P4035 [JSOI2008] 球形空间产生器  考点：模拟退火、高斯消元、构造
 *   https://www.luogu.com.cn/problem/P2538  提高+/省选−  P2538 [SCOI2008] 城堡  考点：动态规划 DP、搜索、二分
 *   https://www.luogu.com.cn/problem/P3607  提高+/省选−  P3607 [USACO17JAN] Subsequence Reversal P  考点：动态规划 DP、枚举、模拟退火
 *   https://www.luogu.com.cn/problem/P3936  提高+/省选−  P3936 Coloring  考点：搜索、模拟退火
 *   https://www.luogu.com.cn/problem/P4360  提高+/省选−  P4360 [CEOI 2004] 锯木厂选址  考点：模拟、动态规划 DP、单调队列
 *   https://www.luogu.com.cn/problem/P4005  省选/NOI−  P4005 [清华集训 2017] 小 Y 和地铁  考点：模拟、搜索、树状数组
 *   https://www.luogu.com.cn/problem/P4044  省选/NOI−  P4044 [AHOI2014/JSOI2014] 保龄球  考点：模拟退火
 *   https://www.luogu.com.cn/problem/P4274  省选/NOI−  P4274 [NOI2004] 小H的小屋  考点：动态规划 DP、贪心、模拟退火
 *   https://www.luogu.com.cn/problem/P5544  省选/NOI−  P5544 [JSOI2016] 炸弹攻击1  考点：模拟退火
 *   https://www.luogu.com.cn/problem/P7962  省选/NOI−  P7962 [NOIP2021] 方差  考点：动态规划 DP、模拟退火、动态规划优化
 *
 */

// 模拟退火：随机化的近似最优化方法，适合"答案函数不好分析、但可以快速计算"的问题。
// 从初始解出发，每次随机扰动得到新解：更优就接受；更差时以概率 exp(-Δ / T) 接受（T 为温度）。
// 温度从 T0 开始乘以 rate（如 0.996）逐渐降低到 Tend：温度高时到处跳，温度低时只做局部微调。
// 调参经验：扰动幅度随温度变小；多跑几次取最优；用 clock() 卡时间，在时限内尽量多跑。
mt19937_64 sa_rng(chrono::steady_clock::now().time_since_epoch().count());
double sa_rand01() { return uniform_real_distribution<double>(0, 1)(sa_rng); }

// 通用框架：最小化 energy(state)。neighbor(state, T) 返回一个随机的相邻解
template <class S, class E, class N>
S simulated_annealing(S init, E energy, N neighbor, double T0 = 1e4, double Tend = 1e-8, double rate = 0.996) {
    S cur = init, best = init;
    double ec = energy(cur), eb = ec;
    for (double T = T0; T > Tend; T *= rate) {
        S nxt = neighbor(cur, T);
        double en = energy(nxt);
        if (en < ec || exp((ec - en) / T) > sa_rand01()) cur = nxt, ec = en;
        if (ec < eb) best = cur, eb = ec;
    }
    return best;
}

// 例（洛谷 P1337 平衡点）：带权费马点，求点 p 使 Σ w_i · |p - q_i| 最小。pts[i] = {x, y, w}
// 退火得到近似解后，再用"步长减半的局部搜索"精修，结果更稳定
pair<double, double> weighted_fermat_point(const vector<array<double, 3>> &pts) {
    using S = pair<double, double>;
    auto energy = [&](const S &p) {
        double s = 0;
        for (auto &q : pts) s += q[2] * hypot(p.first - q[0], p.second - q[1]);
        return s;
    };
    auto neighbor = [&](const S &p, double T) {
        return S{p.first + (sa_rand01() * 2 - 1) * T, p.second + (sa_rand01() * 2 - 1) * T};
    };
    S start{0, 0};
    for (auto &q : pts) start.first += q[0] / pts.size(), start.second += q[1] / pts.size();
    S best = start;
    for (int run = 0; run < 3; run++) {   // 多跑几次取最优
        S r = simulated_annealing(best, energy, neighbor, 1000, 1e-6, 0.995);
        if (energy(r) < energy(best)) best = r;
    }
    double e = energy(best);
    for (double step = 1; step > 1e-9;) {   // 局部精修
        bool moved = false;
        for (auto [dx, dy] : {S{1, 0}, S{-1, 0}, S{0, 1}, S{0, -1}}) {
            S c{best.first + dx * step, best.second + dy * step};
            double ce = energy(c);
            if (ce < e) best = c, e = ce, moved = true;
        }
        if (!moved) step /= 2;
    }
    return best;
}
