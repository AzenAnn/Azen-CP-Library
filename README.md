# cp-library：C++ 算法竞赛模板库

仿照灵茶山艾府的 [codeforces-go](https://github.com/EndlessCheng/codeforces-go) 的维护方式建立的个人 C++ 模板库：
**每个知识点一个文件，文件里同时放"学习路线 + 资料链接 + 自己的笔记 + 题单 + 经过测试的模板代码"**，做一道题补一点，长期积累。

现场赛（ICPC / CCPC）和线上赛（Codeforces / AtCoder / LeetCode）都适用：
线上赛直接复制模板代码；现场赛用 `tools/make_pdf.py` 生成打印版。

## 目录结构

```
cp-library/
├── README.md            本文件（末尾的目录由脚本自动生成）
├── ROADMAP.md           按难度分阶段的学习路线（自动生成）
├── templates/           模板，按专题分目录，编号即学习顺序
│   ├── 01_basic/        基础算法：前缀和、二分、双指针、排序、位运算……
│   ├── 02_ds/           数据结构：单调栈、并查集、树状数组、线段树、平衡树……
│   ├── 03_graph/        图论：BFS/DFS、拓扑、最短路、生成树、连通性、网络流……
│   ├── 04_tree/         树：直径重心、LCA、树上差分、树剖、点分治……
│   ├── 05_math/         数学：取模、数论、组合、矩阵、多项式……
│   ├── 06_dp/           动态规划：线性、背包、区间、树形、状压、数位、优化……
│   ├── 07_string/       字符串：哈希、KMP、Z 函数、Manacher、AC 自动机、SA、SAM……
│   ├── 08_geometry/     计算几何
│   └── 09_misc/         杂项：随机化、交互题、模拟退火
├── tests/               每个已完成模板的对拍测试（随机小数据 + 暴力对比）
├── contest/             比赛工具：main.cpp 骨架、debug.hpp、run.sh 跑样例、stress/ 对拍
├── solutions/           题解库（按平台存放，命名规则见 solutions/README.md）
└── tools/               test_all.sh、gen_index.py、new_template.py、make_pdf.py
```

## 编号与难度

- **编号就是学习顺序**：`02_ds/06_fenwick.hpp` 表示"数据结构专题的第 6 个知识点"。同一专题内按编号从小到大学即可；每个文件头的"前置"写了跨专题的依赖。
- **文件内的【学习顺序】也有编号**，把一个知识点再拆成几个小步骤，比如线段树：1. 单点修改区间查询 → 2. 懒标记 → 3. 多种标记 → 4. 维护复杂信息 → 5. 线段树上二分。
- **难度星级**（大致对应 Codeforces 分数）：★ 入门 800–1300，★★ 提高 1300–1900，★★★ 进阶 1900–2400，★★★★ 高级 2400+。
  [ROADMAP.md](ROADMAP.md) 按星级把所有专题分成四个阶段，适合跨专题交替推进。
- 排序参考了 [OI-wiki](https://oi-wiki.org/) 的目录结构、[cp-algorithms](https://cp-algorithms.com/)、
  [USACO Guide](https://usaco.guide/) 的 Bronze → Platinum 分级，以及灵神题单的难度顺序，并按"前置知识先学"的原则调整过。
  这只是建议，可以按自己的情况调整（改文件头的难度和前置，再运行 `tools/gen_index.py`）。

## 模板文件的结构

每个 `templates/**/*.hpp` 都是同样的格式（参考 `templates/02_ds/07_segment_tree.hpp`）：

```cpp
/**
 * 02_ds/07 线段树（含懒标记）      ← 编号与标题
 * 难度：★★ 提高
 * 前置：02_ds/06 树状数组
 * 状态：DONE / TODO / NOTE         ← 已实现并测试 / 待自己实现 / 没有固定模板
 *
 * 【学习顺序】     本知识点拆成的小步骤
 * 【学习资料】     OI-wiki、cp-algorithms、灵神模板的对应页面（链接都已核实过）
 * 【模板题】       洛谷模板题、Library Checker，用来验证自己的实现
 * 【我的笔记】     学完后用自己的话写：直观理解、易错点
 * 【题单】         做一道补一道：链接  难度  一句话提示
 */
（模板代码）
```

## 代码约定

- **C++17**。所有模板都假设文件开头是 `contest/main.cpp` 里的这几行：
  `#include <bits/stdc++.h>`、`using namespace std;`、`using ll = long long;`
- **每个模板都能直接复制粘贴**，不依赖其他模板（个别地方会在注释里说明可以配合哪个模板使用）。
- 下标从 0 还是从 1 开始、区间开闭，都写在模板的注释里。多数是"从 0 开始、左闭右开 `[l, r)`"，树状数组按惯例从 1 开始。
- 递归深度可能很大的地方（树、图）尽量用 BFS 序或显式栈代替递归。

## 比赛时怎么用

```bash
cd contest
cp main.cpp a.cpp            # 每题一个文件，或直接改 main.cpp
# 把样例存到 samples/1.in、samples/1.out ……
./run.sh a.cpp               # 编译（带越界、溢出检查）并比对所有样例
FAST=1 ./run.sh a.cpp        # 不带检查，跑得更快
cd stress && ./stress.sh     # 对拍：gen.cpp 生成数据，brute.cpp 暴力，sol.cpp 正解
```

代码里可以用 `debug(x, vec, mp)` 打印变量（只在本地 `-DLOCAL` 时生效，提交时自动失效）。

现场赛打印：`python3 tools/make_pdf.py`（或加 `--compact` 去掉注释）生成 `build/cp-library.pdf`，只包含状态为 DONE 的模板代码。

## 如何更新（日常维护流程）

**每做完一道题**
1. 题解存到 `solutions/` 对应目录，开头写链接、难度、一句话思路。
2. 问自己：这题有没有新技巧或新结论？有的话，把"链接 + 难度 + 一句话提示"补进对应模板文件的【题单】，按难度插到合适的位置。
3. 用到了库里还没有的算法 → 见下面"新增模板"。

**学完一个 TODO 专题**
1. 按文件头的【学习顺序】学，在【我的笔记】里写下理解。
2. 在文件下方写出自己的实现，在 `tests/` 里写对拍测试（复制一个已有测试改改即可）。
3. `tools/test_all.sh 专题名` 通过后，把状态改成 DONE。
4. 去做【模板题】，AC 后才算真正可靠。

**新增模板**：`python3 tools/new_template.py 02_ds segment_tree_beats "吉司机线段树" --level 4 --prereq "02_ds/07"`
会生成带标准文件头的模板文件和测试骨架。

**每场比赛后**：赛时卡住的地方，回头看是模板缺了还是模板不好用；修改模板接口后重新跑一遍 `tools/test_all.sh`。

**改完后**：
```bash
tools/test_all.sh                 # 所有测试都要通过
python3 tools/gen_index.py        # 更新下面的目录和 ROADMAP.md
git add -A && git commit -m "segment_tree: 新增区间赋值标记；题单 +3"
```

**定期整理（比如每月一次）**：给题单重新排序、删掉价值不高的题；文件太长就拆分；重新生成打印版 PDF。

## 目录

以下内容由 `python3 tools/gen_index.py` 自动生成。

<!-- INDEX:START -->

共 122 个专题：✅ 已完成 87，⬜ 待实现 28，📝 笔记 7；题单中已收录 1536 道题。

### 01_basic 基础算法（7/12）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [快读快写与比赛骨架](templates\01_basic\01_io.hpp) | ★ | 无 | ✅ 已完成 | 11 |
| 02 | [前缀和与差分](templates\01_basic\02_prefix_sum.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 03 | [二分查找、二分答案与三分](templates\01_basic\03_binary_search.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [双指针与滑动窗口](templates\01_basic\04_two_pointers.hpp) | ★ | 01_basic/02 前缀和与差分 | ✅ 已完成 | 15 |
| 05 | [排序与离散化](templates\01_basic\05_sort_discrete.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 06 | [位运算](templates\01_basic\06_bits.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 07 | [贪心常见模型](templates\01_basic\07_greedy.hpp) | ★ | 无 | 📝 笔记 | 15 |
| 08 | [高精度](templates\01_basic\08_bignum.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 09 | [倍增](templates\01_basic\09_binary_lifting.hpp) | ★★ | 01_basic/03 二分查找、二分答案与三分 | 📝 笔记 | 15 |
| 10 | [分治](templates\01_basic\10_divide_conquer.hpp) | ★★ | 01_basic/05 排序与离散化 | 📝 笔记 | 15 |
| 11 | [构造](templates\01_basic\11_construction.hpp) | ★★ | 无 | 📝 笔记 | 15 |
| 12 | [搜索：DFS、BFS、剪枝](templates\01_basic\12_search.hpp) | ★★ | 01_basic/10 分治 | 📝 笔记 | 14 |

### 02_ds 数据结构（17/21）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [栈与单调栈](templates\02_ds\01_stack_monotone.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 02 | [单调队列](templates\02_ds\02_monotone_queue.hpp) | ★ | 02_ds/01 栈与单调栈 | ✅ 已完成 | 15 |
| 03 | [堆与优先队列](templates\02_ds\03_heap.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [并查集](templates\02_ds\04_dsu.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 05 | [ST 表](templates\02_ds\05_sparse_table.hpp) | ★★ | 01_basic/09 倍增 | ✅ 已完成 | 15 |
| 06 | [树状数组](templates\02_ds\06_fenwick.hpp) | ★★ | 01_basic/02 前缀和与差分、01_basic/06 位运算 | ✅ 已完成 | 15 |
| 07 | [线段树（含懒标记）](templates\02_ds\07_segment_tree.hpp) | ★★ | 02_ds/06 树状数组 | ✅ 已完成 | 15 |
| 08 | [字典树 Trie 与 01-Trie](templates\02_ds\08_trie.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 09 | [分块与根号分治](templates\02_ds\09_sqrt_decomposition.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 10 | [莫队](templates\02_ds\10_mo.hpp) | ★★★ | 02_ds/09 分块与根号分治 | ✅ 已完成 | 15 |
| 11 | [线段树进阶](templates\02_ds\11_segment_tree_adv.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 12 | [平衡树](templates\02_ds\12_balanced_tree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 13 | [可持久化数据结构](templates\02_ds\13_persistent.hpp) | ★★★ | 02_ds/11 线段树进阶、02_ds/08 字典树 Trie 与 01-Trie | ✅ 已完成 | 15 |
| 14 | [珂朵莉树（ODT）](templates\02_ds\14_odt.hpp) | ★★★ | 02_ds/12 平衡树 | ✅ 已完成 | 15 |
| 15 | [CDQ 分治与整体二分](templates\02_ds\15_cdq_offline.hpp) | ★★★★ | 01_basic/10 分治、02_ds/06 树状数组 | ✅ 已完成 | 15 |
| 16 | [可并堆（左偏树）](templates\02_ds\16_leftist_tree.hpp) | ★★★★ | 02_ds/03 堆与优先队列 | ✅ 已完成 | 12 |
| 17 | [Link-Cut Tree](templates\02_ds\17_lct.hpp) | ★★★★ | 02_ds/12 平衡树、04_tree/04 树链剖分 | ✅ 已完成 | 15 |
| 18 | [李超线段树](templates\02_ds\18_li_chao_tree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ⬜ 待实现 | 8 |
| 19 | [线段树合并与分裂](templates\02_ds\19_seg_merge_split.hpp) | ★★★★ | 02_ds/11 线段树进阶、02_ds/13 可持久化数据结构 | ⬜ 待实现 | 8 |
| 20 | [树套树](templates\02_ds\20_tree_in_tree.hpp) | ★★★★ | 02_ds/11 线段树进阶、02_ds/12 平衡树 | ⬜ 待实现 | 8 |
| 21 | [K-D Tree](templates\02_ds\21_kdtree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ⬜ 待实现 | 8 |

### 03_graph 图论（12/17）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [存图与图的遍历](templates\03_graph\01_graph_basic.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 02 | [拓扑排序](templates\03_graph\02_topo.hpp) | ★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 03 | [最短路](templates\03_graph\03_shortest_path.hpp) | ★★ | 03_graph/01 存图与图的遍历、02_ds/03 堆与优先队列 | ✅ 已完成 | 15 |
| 04 | [最小生成树](templates\03_graph\04_mst.hpp) | ★★ | 02_ds/04 并查集 | ✅ 已完成 | 15 |
| 05 | [强连通分量与缩点](templates\03_graph\05_scc.hpp) | ★★ | 03_graph/02 拓扑排序 | ✅ 已完成 | 15 |
| 06 | [割点、桥与双连通分量](templates\03_graph\06_bcc.hpp) | ★★★ | 03_graph/05 强连通分量与缩点 | ✅ 已完成 | 15 |
| 07 | [二分图](templates\03_graph\07_bipartite.hpp) | ★★★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 08 | [差分约束](templates\03_graph\08_diff_constraints.hpp) | ★★★ | 03_graph/03 最短路 | ✅ 已完成 | 15 |
| 09 | [2-SAT](templates\03_graph\09_two_sat.hpp) | ★★★ | 03_graph/05 强连通分量与缩点 | ✅ 已完成 | 15 |
| 10 | [欧拉路径与欧拉回路](templates\03_graph\10_euler.hpp) | ★★★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 11 | [网络流：最大流与最小割](templates\03_graph\11_max_flow.hpp) | ★★★ | 03_graph/03 最短路 | ✅ 已完成 | 15 |
| 12 | [最小费用最大流](templates\03_graph\12_min_cost_flow.hpp) | ★★★★ | 03_graph/11 网络流：最大流与最小割 | ✅ 已完成 | 15 |
| 13 | [K 短路](templates\03_graph\13_kth_path.hpp) | ★★★ | 03_graph/03 最短路（Dijkstra/SPFA） | ⬜ 待实现 | 6 |
| 14 | [最小树形图（朱刘算法 / Edmonds）](templates\03_graph\14_dmst.hpp) | ★★★★ | 03_graph/04 最小生成树 | ⬜ 待实现 | 6 |
| 15 | [上下界网络流](templates\03_graph\15_flow_bound.hpp) | ★★★★ | 03_graph/11 最大流（Dinic） | ⬜ 待实现 | 6 |
| 16 | [一般图匹配（带花树 Blossom）](templates\03_graph\16_general_match.hpp) | ★★★★ | 03_graph/07 二分图匹配（匈牙利 / Hopcroft-Karp） | ⬜ 待实现 | 6 |
| 17 | [圆方树](templates\03_graph\17_block_forest.hpp) | ★★★★ | 03_graph/06 Tarjan（割点 / 点双连通分量） | ⬜ 待实现 | 7 |

### 04_tree 树（8/10）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [树的基础：直径、重心、DFS 序](templates\04_tree\01_tree_basic.hpp) | ★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 02 | [最近公共祖先（LCA）](templates\04_tree\02_lca.hpp) | ★★ | 04_tree/01 树的基础：直径、重心、DFS 序、01_basic/09 倍增 | ✅ 已完成 | 15 |
| 03 | [树上差分与树上前缀和](templates\04_tree\03_tree_diff.hpp) | ★★ | 04_tree/02 最近公共祖先（LCA）、01_basic/02 前缀和与差分 | ✅ 已完成 | 13 |
| 04 | [树链剖分](templates\04_tree\04_hld.hpp) | ★★★ | 04_tree/02 最近公共祖先（LCA）、02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 05 | [树上启发式合并](templates\04_tree\05_dsu_on_tree.hpp) | ★★★ | 04_tree/04 树链剖分 | ✅ 已完成 | 15 |
| 06 | [树哈希与树同构](templates\04_tree\06_tree_hash.hpp) | ★★★ | 04_tree/01 树的基础：直径、重心、DFS 序 | ✅ 已完成 | 15 |
| 07 | [点分治](templates\04_tree\07_centroid_decomp.hpp) | ★★★★ | 04_tree/01 树的基础：直径、重心、DFS 序、01_basic/10 分治 | ✅ 已完成 | 15 |
| 08 | [虚树](templates\04_tree\08_virtual_tree.hpp) | ★★★★ | 04_tree/02 最近公共祖先（LCA） | ✅ 已完成 | 15 |
| 09 | [动态点分治（点分树）](templates\04_tree\09_dynamic_tree_divide.hpp) | ★★★★ | 04_tree/07 静态点分治 | ⬜ 待实现 | 6 |
| 10 | [树上随机游走](templates\04_tree\10_tree_random_walk.hpp) | ★★★★ | 04_tree/01 树的遍历与直径、05_math/01 概率期望 | ⬜ 待实现 | 6 |

### 05_math 数学（16/24）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [取模运算与快速幂](templates\05_math\01_modint.hpp) | ★ | 无 | ✅ 已完成 | 11 |
| 02 | [GCD 与扩展欧几里得](templates\05_math\02_gcd.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 03 | [素数、筛法与分解质因数](templates\05_math\03_prime_sieve.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [乘法逆元](templates\05_math\04_inverse.hpp) | ★★ | 05_math/01 取模运算与快速幂、05_math/02 GCD 与扩展欧几里得 | ✅ 已完成 | 15 |
| 05 | [组合数与计数原理](templates\05_math\05_combinatorics.hpp) | ★★ | 05_math/04 乘法逆元 | ✅ 已完成 | 15 |
| 06 | [欧拉函数与欧拉定理](templates\05_math\06_euler_phi.hpp) | ★★ | 05_math/03 素数、筛法与分解质因数 | ✅ 已完成 | 15 |
| 07 | [矩阵与矩阵快速幂](templates\05_math\07_matrix.hpp) | ★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 08 | [中国剩余定理](templates\05_math\08_crt.hpp) | ★★★ | 05_math/02 GCD 与扩展欧几里得 | ✅ 已完成 | 15 |
| 09 | [高斯消元](templates\05_math\09_gauss.hpp) | ★★★ | 05_math/07 矩阵与矩阵快速幂 | ✅ 已完成 | 15 |
| 10 | [线性基](templates\05_math\10_linear_basis.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 11 | [数论分块（整除分块）](templates\05_math\11_number_block.hpp) | ★★★ | 无 | ✅ 已完成 | 15 |
| 12 | [博弈论](templates\05_math\12_game.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 13 | [莫比乌斯反演](templates\05_math\13_mobius.hpp) | ★★★★ | 05_math/11 数论分块（整除分块）、05_math/06 欧拉函数与欧拉定理 | ✅ 已完成 | 15 |
| 14 | [离散对数 BSGS](templates\05_math\14_bsgs.hpp) | ★★★★ | 05_math/04 乘法逆元 | ✅ 已完成 | 13 |
| 15 | [Miller-Rabin 与 Pollard-Rho](templates\05_math\15_pollard_rho.hpp) | ★★★★ | 05_math/03 素数、筛法与分解质因数 | ✅ 已完成 | 8 |
| 16 | [FFT / NTT 多项式乘法](templates\05_math\16_fft_ntt.hpp) | ★★★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 17 | [Lucas 定理与扩展 Lucas](templates\05_math\17_lucas.hpp) | ★★★ | 05_math/05 组合数学基础（逆元、组合数） | ⬜ 待实现 | 6 |
| 18 | [阶与原根](templates\05_math\18_primitive_root.hpp) | ★★★ | 05_math/04 欧拉函数、05_math/06 快速幂 / 费马小定理 | ⬜ 待实现 | 6 |
| 19 | [卡特兰数与斯特林数](templates\05_math\19_catalan.hpp) | ★★★ | 05_math/05 组合数学基础 | ⬜ 待实现 | 8 |
| 20 | [杜教筛](templates\05_math\20_du_sieve.hpp) | ★★★★ | 05_math/13 线性筛 / 莫比乌斯反演 | ⬜ 待实现 | 6 |
| 21 | [FWT（快速沃尔什变换）](templates\05_math\21_fwt.hpp) | ★★★★ | 05_math/16 FFT / NTT | ⬜ 待实现 | 6 |
| 22 | [多项式进阶（牛顿迭代、逆元/开方/ln/exp）](templates\05_math\22_poly_ops.hpp) | ★★★★ | 05_math/16 FFT / NTT | ⬜ 待实现 | 7 |
| 23 | [单纯形法（线性规划）](templates\05_math\23_simplex.hpp) | ★★★★ | 05_math/09 高斯消元 | ⬜ 待实现 | 6 |
| 24 | [拉格朗日插值](templates\05_math\24_lagrange_interp.hpp) | ★★★ | 05_math/04 同余基础、05_math/05 逆元 | ⬜ 待实现 | 6 |

### 06_dp 动态规划（10/15）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [线性 DP 入门与记忆化搜索](templates\06_dp\01_dp_basic.hpp) | ★ | 无 | 📝 笔记 | 15 |
| 02 | [LIS、LCS 与编辑距离](templates\06_dp\02_lis_lcs.hpp) | ★ | 06_dp/01 线性 DP 入门与记忆化搜索、01_basic/03 二分查找、二分答案与三分 | ✅ 已完成 | 13 |
| 03 | [背包 DP](templates\06_dp\03_knapsack.hpp) | ★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 04 | [区间 DP](templates\06_dp\04_interval_dp.hpp) | ★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 05 | [树形 DP 与换根 DP](templates\06_dp\05_tree_dp.hpp) | ★★ | 04_tree/01 树的基础：直径、重心、DFS 序 | ✅ 已完成 | 15 |
| 06 | [状压 DP](templates\06_dp\06_bitmask_dp.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 07 | [数位 DP](templates\06_dp\07_digit_dp.hpp) | ★★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 08 | [单调队列 / 单调栈优化 DP](templates\06_dp\08_dp_opt_monoqueue.hpp) | ★★★ | 02_ds/02 单调队列 | ✅ 已完成 | 15 |
| 09 | [概率与期望 DP](templates\06_dp\09_dp_expectation.hpp) | ★★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 10 | [斜率优化与凸包技巧](templates\06_dp\10_dp_opt_slope.hpp) | ★★★★ | 06_dp/08 单调队列 / 单调栈优化 DP | ✅ 已完成 | 15 |
| 11 | [四边形不等式与决策单调性](templates\06_dp\11_dp_opt_quadrangle.hpp) | ★★★★ | 06_dp/04 区间 DP | ✅ 已完成 | 15 |
| 12 | [插头 DP（轮廓线 DP）](templates\06_dp\12_plug_dp.hpp) | ★★★★ | 06_dp/06 状态压缩 DP | ⬜ 待实现 | 6 |
| 13 | [动态 DP](templates\06_dp\13_dynamic_dp.hpp) | ★★★★ | 06_dp/05 树形 DP、05_math/07 矩阵乘法 / 矩阵快速幂 | ⬜ 待实现 | 6 |
| 14 | [DP 套 DP](templates\06_dp\14_dp_of_dp.hpp) | ★★★★ | 06_dp/06 状态压缩 DP、06_dp/02 线性 DP | ⬜ 待实现 | 6 |
| 15 | [WQS 二分与 Slope Trick](templates\06_dp\15_wqs_slope_trick.hpp) | ★★★★ | 06_dp/10 斜率优化 DP | ⬜ 待实现 | 7 |

### 07_string 字符串（9/11）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [字符串哈希](templates\07_string\01_string_hash.hpp) | ★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 02 | [KMP 与前缀函数](templates\07_string\02_kmp.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 03 | [Z 函数（扩展 KMP）](templates\07_string\03_z_function.hpp) | ★★ | 07_string/02 KMP 与前缀函数 | ✅ 已完成 | 11 |
| 04 | [Manacher 最长回文子串](templates\07_string\04_manacher.hpp) | ★★★ | 07_string/03 Z 函数（扩展 KMP） | ✅ 已完成 | 15 |
| 05 | [最小表示法](templates\07_string\05_min_repr.hpp) | ★★★ | 无 | ✅ 已完成 | 6 |
| 06 | [AC 自动机](templates\07_string\06_ac_automaton.hpp) | ★★★ | 02_ds/08 字典树 Trie 与 01-Trie、07_string/02 KMP 与前缀函数 | ✅ 已完成 | 15 |
| 07 | [后缀数组](templates\07_string\07_suffix_array.hpp) | ★★★★ | 01_basic/05 排序与离散化 | ✅ 已完成 | 15 |
| 08 | [后缀自动机（SAM）](templates\07_string\08_sam.hpp) | ★★★★ | 07_string/07 后缀数组 | ✅ 已完成 | 15 |
| 09 | [回文自动机（PAM）](templates\07_string\09_pam.hpp) | ★★★★ | 07_string/04 Manacher 最长回文子串 | ✅ 已完成 | 12 |
| 10 | [广义 SAM](templates\07_string\10_general_sam.hpp) | ★★★★ | 07_string/08 后缀自动机（SAM） | ⬜ 待实现 | 6 |
| 11 | [序列自动机](templates\07_string\11_seq_automaton.hpp) | ★★★ | 07_string/08 后缀自动机（理解自动机思想） | ⬜ 待实现 | 6 |

### 08_geometry 计算几何（6/8）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [点、向量与基本运算](templates\08_geometry\01_geo_basic.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 02 | [凸包](templates\08_geometry\02_convex_hull.hpp) | ★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 15 |
| 03 | [旋转卡壳](templates\08_geometry\03_rotating_calipers.hpp) | ★★★ | 08_geometry/02 凸包 | ✅ 已完成 | 11 |
| 04 | [扫描线：矩形面积并](templates\08_geometry\04_scanline.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 05 | [平面最近点对](templates\08_geometry\05_closest_pair.hpp) | ★★★ | 01_basic/10 分治 | ✅ 已完成 | 8 |
| 06 | [半平面交](templates\08_geometry\06_half_plane.hpp) | ★★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 11 |
| 07 | [三维几何](templates\08_geometry\07_3d.hpp) | ★★★★ | 08_geometry/01 二维计算几何基础 | ⬜ 待实现 | 6 |
| 08 | [最小圆覆盖](templates\08_geometry\08_min_circle.hpp) | ★★★ | 08_geometry/01 二维计算几何基础 | ⬜ 待实现 | 6 |

### 09_misc 杂项（2/4）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [随机数与防卡哈希](templates\09_misc\01_random_hash.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 02 | [交互题](templates\09_misc\02_interactive.hpp) | ★★ | 01_basic/03 二分查找、二分答案与三分 | 📝 笔记 | 15 |
| 03 | [模拟退火](templates\09_misc\03_simulated_annealing.hpp) | ★★★ | 09_misc/01 随机数与防卡哈希 | ✅ 已完成 | 15 |
| 04 | [折半搜索 / Meet in the Middle](templates\09_misc\04_meet_in_middle.hpp) | ★★ | 01_basic/03 二分查找、01_basic/12 搜索 | ⬜ 待实现 | 7 |

<!-- INDEX:END -->

## 参考与致谢

- 维护方式和题单写法参考了 [EndlessCheng/codeforces-go](https://github.com/EndlessCheng/codeforces-go)（MIT 协议），本库的代码是独立编写的 C++ 实现，没有复制其中的代码。
- 学习资料：[OI-wiki](https://oi-wiki.org/)、[cp-algorithms](https://cp-algorithms.com/)、[USACO Guide](https://usaco.guide/)。
- 验证用的题目：[洛谷](https://www.luogu.com.cn/)、[Library Checker](https://judge.yosupo.jp/)。
