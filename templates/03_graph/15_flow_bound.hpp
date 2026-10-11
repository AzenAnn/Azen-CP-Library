/**
 * 03_graph/15 上下界网络流
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：03_graph/11 最大流（Dinic）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 无源汇上下界可行流：建超级源汇，下界由附加边满足
 *   2. 有源汇上下界可行流：连 t→s 容量 inf 化为无源汇
 *   3. 有源汇上下界最大流：先求可行流，再在残量网络上 s→t 增广
 *   4. 有源汇上下界最小流：先求可行流，再 t→s 退流
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/graph/flow/bound/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P5192  P5192 Zoj3229 Shoot the Bullet（无源汇可行流）
 *   https://www.luogu.com.cn/problem/P4843  P4843 清理雪道（有源汇最小流）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P5192  提高+  P5192 Shoot the Bullet  考点：无源汇上下界可行流
 *   https://www.luogu.com.cn/problem/P4043  提高+  P4043 [AHOI2014/JSOI2014] 支线剧情  考点：下界建模
 *   https://www.luogu.com.cn/problem/P4843  省选−  P4843 清理雪道  考点：有源汇上下界最小流
 *   https://www.luogu.com.cn/problem/P3980  省选−  P3980 [NOI2008] 志愿者招募  考点：上下界费用流 / 线性规划
 *   https://www.luogu.com.cn/problem/P4553  省选/NOI−  P4553 80人环游世界  考点：上下界最小费用可行流
 *   https://www.luogu.com.cn/problem/P2469  省选−  P2469 [SDOI2010] 星际竞速  考点：上下界建模
 *
 */

// TODO：在这里写出实现
