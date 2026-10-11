/**
 * 05_math/24 拉格朗日插值
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/04 同余基础、05_math/05 逆元
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 插值公式：f(x) = Σ y_i · Π_{j≠i} (x − x_j)/(x_i − x_j)
 *   2. n 个点确定次数 < n 的多项式；单点求值 O(n²)
 *   3. 横坐标连续（x_i = i）时：前缀积/后缀积优化到 O(n)
 *   4. 应用：自然数幂和、DP 转多项式后单点求值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/numerical/interp/
 *   OI-wiki        https://oi-wiki.org/math/poly/lagrange/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4781  P4781 【模板】拉格朗日插值
 *   https://www.luogu.com.cn/problem/P4463  P4463 [国家集训队] JOLO（插值应用）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4781  提高  P4781 【模板】拉格朗日插值  考点：O(n²) 插值
 *   https://www.luogu.com.cn/problem/P5158  提高+  P5158 [SDOI2018] 旧试题（幂和）  考点：连续点插值求幂和
 *   https://codeforces.com/problemset/problem/622/F  CF2300  CF622F The Sum of the k-th Powers  考点：拉插求幂和
 *   https://www.luogu.com.cn/problem/P4593  省选−  P4593 [TJOI2018] 教科书般的亵渎  考点：拉插 + 组合
 *   https://www.luogu.com.cn/problem/P4463  省选/NOI−  P4463 [国家集训队] JOLO  考点：插值综合
 *   https://codeforces.com/problemset/problem/1155/E  CF2600  CF1155E Guess the Permutation  考点：交互 + 插值思想
 *
 */

// TODO：在这里写出实现
