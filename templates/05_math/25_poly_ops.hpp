/**
 * 05_math/25 多项式进阶（牛顿迭代、逆元/开方/ln/exp）
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：05_math/17 FFT / NTT 多项式乘法
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 多项式求逆：牛顿迭代 G_{2n} = G_n(2 − F·G_n) mod x^{2n}
 *   2. 多项式除法 / 取模：翻转系数转求逆
 *   3. 多项式开方、ln、exp：求导积分 + 牛顿迭代
 *   4. 应用：生成函数卷积计数、分治 NTT、多点求值/插值
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/poly/inv/
 *   OI-wiki        https://oi-wiki.org/math/poly/div-mod/
 *   OI-wiki        https://oi-wiki.org/math/poly/sqrt/
 *   OI-wiki        https://oi-wiki.org/math/poly/ln-exp/
 *   OI-wiki        https://oi-wiki.org/math/poly/newton/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P4238  P4238 【模板】多项式求逆
 *   https://www.luogu.com.cn/problem/P5205  P5205 【模板】多项式开根
 *   https://www.luogu.com.cn/problem/P4725  P4725 【模板】多项式对数函数 / 指数函数
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P4238  省选−  P4238 【模板】多项式求逆  考点：牛顿迭代
 *   https://www.luogu.com.cn/problem/P4512  省选−  P4512 【模板】多项式除法  考点：求逆 + 翻转
 *   https://www.luogu.com.cn/problem/P5245  省选−  P5245 【模板】多项式快速幂  考点：ln + exp
 *   https://www.luogu.com.cn/problem/P5205  省选−  P5205 【模板】多项式开根  考点：牛顿迭代 / 二次剩余
 *   https://www.luogu.com.cn/problem/P4725  省选/NOI−  P4725 【模板】多项式 ln / exp  考点：求导积分
 *   https://www.luogu.com.cn/problem/P4721  省选−  P4721 【模板】分治 FFT  考点：CDQ 分治 + NTT
 *   https://www.luogu.com.cn/problem/P5281  省选/NOI−  P5281 【模板】多项式多点求值  考点：分治 + 取模
 *
 */

// TODO：在这里写出实现
