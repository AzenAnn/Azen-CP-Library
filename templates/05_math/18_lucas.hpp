/**
 * 05_math/18 Lucas 定理与扩展 Lucas
 * 难度：★★★ 进阶（约 CF 1900–2400）
 * 前置：05_math/05 组合数与计数原理
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. Lucas 定理：C(n, m) mod p = Π C(ni, mi) mod p（p 为素数，n, m 按 p 进制展开）
 *   2. 预处理 p 以内的阶乘与逆元，O(p + log_p n) 查询
 *   3. 扩展 Lucas：模数为合数 → CRT 分解为素数幂，分别计算后合并
 *   4. 素数幂模组合数：去除 p 因子后计算
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/math/number-theory/lucas/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P3807  P3807 【模板】卢卡斯定理 / Lucas Theorem
 *   https://www.luogu.com.cn/problem/P4720  P4720 【模板】扩展卢卡斯定理 / exLucas
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3807  提高  P3807 【模板】Lucas 定理  考点：Lucas
 *   https://www.luogu.com.cn/problem/P4349  提高  P4349 [CERC2016] 机氨酸  考点：Lucas 应用
 *   https://www.luogu.com.cn/problem/P6669  提高+  P6669 [清华集训 2016] 组合数问题  考点：Lucas 计数
 *   https://www.luogu.com.cn/problem/P2480  提高+  P2480 [SDOI2010] 古代猪文  考点：Lucas + CRT + BSGS
 *   https://www.luogu.com.cn/problem/P4720  省选−  P4720 【模板】扩展 Lucas  考点：exLucas + CRT
 *   https://www.luogu.com.cn/problem/P4463  省选/NOI−  P4463 [国家集训队] JOLO  考点：exLucas 综合
 *
 */

// TODO：在这里写出实现
