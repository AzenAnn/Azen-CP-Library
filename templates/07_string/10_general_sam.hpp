/**
 * 07_string/10 广义 SAM
 * 难度：★★★★ 高级（约 CF 2400+）
 * 前置：07_string/08 后缀自动机（SAM）
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1. 广义 SAM：对多个串（或 Trie 树）建一个 SAM，匹配任意子串
 *   2. Trie 上 BFS 建 SAM：按父亲节点 last 插入，避免重复建状态
 *   3. 与普通 SAM 区别：last 更新策略、重复插入同一前缀
 *   4. 应用：多串公共子串、字典树子串统计
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/string/general-sam/
 *
 * 【模板题 / 入门题】
 *   https://www.luogu.com.cn/problem/P6139  P6139 【模板】广义后缀自动机（广义 SAM）
 *   https://www.luogu.com.cn/problem/P3804  P3804 【模板】后缀自动机（前置）
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P3804  提高+/省选−  P3804 【模板】后缀自动机  考点：SAM 基础
 *   https://www.luogu.com.cn/problem/P6139  省选−  P6139 【模板】广义 SAM  考点：Trie 上 BFS 建 SAM
 *   https://www.luogu.com.cn/problem/P3181  省选−  P3181 [HAOI2016] 找相同字符  考点：广义 SAM 计数
 *   https://www.luogu.com.cn/problem/P4022  省选−  P4022 [CTSC2012] 熟悉的文章  考点：广义 SAM + 二分
 *   https://www.luogu.com.cn/problem/P6500  省选/NOI−  P6500 [World Cup 2014] 传球游戏（多串匹配）  考点：广义 SAM
 *   https://codeforces.com/problemset/problem/1037/H  CF2600  CF1037H Security  考点：SAM + 线段树合并
 *
 */

// TODO：在这里写出实现
