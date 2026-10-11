# 学习路线（按难度分阶段）

本文件由 `python3 tools/gen_index.py` 自动生成，请不要手动修改。

同一阶段内建议各专题交替推进：每学完一个知识点，就去做它的模板题和题单里的题。括号中的"前置"表示学这一项之前最好先掌握的内容。

图标：✅ 模板代码已实现并通过测试　⬜ 待自己实现　📝 没有固定模板，以笔记和题单为主

## 阶段一：入门 ★

**基础算法**

- ✅ [01_basic/01 快读快写与比赛骨架](templates\01_basic\01_io.hpp)
- ✅ [01_basic/02 前缀和与差分](templates\01_basic\02_prefix_sum.hpp)
- ✅ [01_basic/03 二分查找、二分答案与三分](templates\01_basic\03_binary_search.hpp)
- ✅ [01_basic/04 双指针与滑动窗口](templates\01_basic\04_two_pointers.hpp)（前置：01_basic/02 前缀和与差分）
- ✅ [01_basic/05 排序与离散化](templates\01_basic\05_sort_discrete.hpp)
- ✅ [01_basic/06 位运算](templates\01_basic\06_bits.hpp)
- 📝 [01_basic/07 贪心常见模型](templates\01_basic\07_greedy.hpp)
- ✅ [01_basic/08 高精度](templates\01_basic\08_bignum.hpp)

**数据结构**

- ✅ [02_ds/01 栈与单调栈](templates\02_ds\01_stack_monotone.hpp)
- ✅ [02_ds/02 单调队列](templates\02_ds\02_monotone_queue.hpp)（前置：02_ds/01 栈与单调栈）
- ✅ [02_ds/03 堆与优先队列](templates\02_ds\03_heap.hpp)
- ✅ [02_ds/04 并查集](templates\02_ds\04_dsu.hpp)

**图论**

- ✅ [03_graph/01 存图与图的遍历](templates\03_graph\01_graph_basic.hpp)
- ✅ [03_graph/02 拓扑排序](templates\03_graph\02_topo.hpp)（前置：03_graph/01 存图与图的遍历）

**树**

- ✅ [04_tree/01 树的基础：直径、重心、DFS 序](templates\04_tree\01_tree_basic.hpp)（前置：03_graph/01 存图与图的遍历）

**数学**

- ✅ [05_math/01 取模运算与快速幂](templates\05_math\01_modint.hpp)
- ✅ [05_math/02 GCD 与扩展欧几里得](templates\05_math\02_gcd.hpp)
- ✅ [05_math/03 素数、筛法与分解质因数](templates\05_math\03_prime_sieve.hpp)

**动态规划**

- 📝 [06_dp/01 线性 DP 入门与记忆化搜索](templates\06_dp\01_dp_basic.hpp)
- ✅ [06_dp/02 LIS、LCS 与编辑距离](templates\06_dp\02_lis_lcs.hpp)（前置：06_dp/01 线性 DP 入门与记忆化搜索、01_basic/03 二分查找、二分答案与三分）

## 阶段二：提高 ★★

**基础算法**

- 📝 [01_basic/09 倍增](templates\01_basic\09_binary_lifting.hpp)（前置：01_basic/03 二分查找、二分答案与三分）
- 📝 [01_basic/10 分治](templates\01_basic\10_divide_conquer.hpp)（前置：01_basic/05 排序与离散化）
- 📝 [01_basic/11 构造](templates\01_basic\11_construction.hpp)
- 📝 [01_basic/12 搜索：DFS、BFS、剪枝](templates\01_basic\12_search.hpp)（前置：01_basic/10 分治）

**数据结构**

- ✅ [02_ds/05 ST 表](templates\02_ds\05_sparse_table.hpp)（前置：01_basic/09 倍增）
- ✅ [02_ds/06 树状数组](templates\02_ds\06_fenwick.hpp)（前置：01_basic/02 前缀和与差分、01_basic/06 位运算）
- ✅ [02_ds/07 线段树（含懒标记）](templates\02_ds\07_segment_tree.hpp)（前置：02_ds/06 树状数组）
- ✅ [02_ds/08 字典树 Trie 与 01-Trie](templates\02_ds\08_trie.hpp)

**图论**

- ✅ [03_graph/03 最短路](templates\03_graph\03_shortest_path.hpp)（前置：03_graph/01 存图与图的遍历、02_ds/03 堆与优先队列）
- ✅ [03_graph/04 最小生成树](templates\03_graph\04_mst.hpp)（前置：02_ds/04 并查集）
- ✅ [03_graph/05 强连通分量与缩点](templates\03_graph\05_scc.hpp)（前置：03_graph/02 拓扑排序）

**树**

- ✅ [04_tree/02 最近公共祖先（LCA）](templates\04_tree\02_lca.hpp)（前置：04_tree/01 树的基础：直径、重心、DFS 序、01_basic/09 倍增）
- ✅ [04_tree/03 树上差分与树上前缀和](templates\04_tree\03_tree_diff.hpp)（前置：04_tree/02 最近公共祖先（LCA）、01_basic/02 前缀和与差分）

**数学**

- ✅ [05_math/04 乘法逆元](templates\05_math\04_inverse.hpp)（前置：05_math/01 取模运算与快速幂、05_math/02 GCD 与扩展欧几里得）
- ✅ [05_math/05 组合数与计数原理](templates\05_math\05_combinatorics.hpp)（前置：05_math/04 乘法逆元）
- ✅ [05_math/06 欧拉函数与欧拉定理](templates\05_math\06_euler_phi.hpp)（前置：05_math/03 素数、筛法与分解质因数）
- ✅ [05_math/07 矩阵与矩阵快速幂](templates\05_math\07_matrix.hpp)（前置：05_math/01 取模运算与快速幂）

**动态规划**

- ✅ [06_dp/03 背包 DP](templates\06_dp\03_knapsack.hpp)（前置：06_dp/01 线性 DP 入门与记忆化搜索）
- ✅ [06_dp/04 区间 DP](templates\06_dp\04_interval_dp.hpp)（前置：06_dp/01 线性 DP 入门与记忆化搜索）
- ✅ [06_dp/05 树形 DP 与换根 DP](templates\06_dp\05_tree_dp.hpp)（前置：04_tree/01 树的基础：直径、重心、DFS 序）

**字符串**

- ✅ [07_string/01 字符串哈希](templates\07_string\01_string_hash.hpp)（前置：05_math/01 取模运算与快速幂）
- ✅ [07_string/02 KMP 与前缀函数](templates\07_string\02_kmp.hpp)
- ✅ [07_string/03 Z 函数（扩展 KMP）](templates\07_string\03_z_function.hpp)（前置：07_string/02 KMP 与前缀函数）

**计算几何**

- ✅ [08_geometry/01 点、向量与基本运算](templates\08_geometry\01_geo_basic.hpp)

**杂项**

- ✅ [09_misc/01 随机数与防卡哈希](templates\09_misc\01_random_hash.hpp)
- 📝 [09_misc/02 交互题](templates\09_misc\02_interactive.hpp)（前置：01_basic/03 二分查找、二分答案与三分）
- ⬜ [09_misc/04 折半搜索 / Meet in the Middle](templates\09_misc\04_meet_in_middle.hpp)（前置：01_basic/03 二分查找、01_basic/12 搜索）

## 阶段三：进阶 ★★★

**数据结构**

- ✅ [02_ds/09 分块与根号分治](templates\02_ds\09_sqrt_decomposition.hpp)（前置：02_ds/07 线段树（含懒标记））
- ✅ [02_ds/10 莫队](templates\02_ds\10_mo.hpp)（前置：02_ds/09 分块与根号分治）
- ✅ [02_ds/11 线段树进阶](templates\02_ds\11_segment_tree_adv.hpp)（前置：02_ds/07 线段树（含懒标记））
- ✅ [02_ds/12 平衡树](templates\02_ds\12_balanced_tree.hpp)（前置：02_ds/07 线段树（含懒标记））
- ✅ [02_ds/13 可持久化数据结构](templates\02_ds\13_persistent.hpp)（前置：02_ds/11 线段树进阶、02_ds/08 字典树 Trie 与 01-Trie）
- ✅ [02_ds/14 珂朵莉树（ODT）](templates\02_ds\14_odt.hpp)（前置：02_ds/12 平衡树）
- ⬜ [02_ds/18 李超线段树](templates\02_ds\18_li_chao_tree.hpp)（前置：02_ds/07 线段树（含懒标记））
- ⬜ [02_ds/21 K-D Tree](templates\02_ds\21_kdtree.hpp)（前置：02_ds/07 线段树（含懒标记））

**图论**

- ✅ [03_graph/06 割点、桥与双连通分量](templates\03_graph\06_bcc.hpp)（前置：03_graph/05 强连通分量与缩点）
- ✅ [03_graph/07 二分图](templates\03_graph\07_bipartite.hpp)（前置：03_graph/01 存图与图的遍历）
- ✅ [03_graph/08 差分约束](templates\03_graph\08_diff_constraints.hpp)（前置：03_graph/03 最短路）
- ✅ [03_graph/09 2-SAT](templates\03_graph\09_two_sat.hpp)（前置：03_graph/05 强连通分量与缩点）
- ✅ [03_graph/10 欧拉路径与欧拉回路](templates\03_graph\10_euler.hpp)（前置：03_graph/01 存图与图的遍历）
- ✅ [03_graph/11 网络流：最大流与最小割](templates\03_graph\11_max_flow.hpp)（前置：03_graph/03 最短路）
- ⬜ [03_graph/13 K 短路](templates\03_graph\13_kth_path.hpp)（前置：03_graph/03 最短路（Dijkstra/SPFA））

**树**

- ✅ [04_tree/04 树链剖分](templates\04_tree\04_hld.hpp)（前置：04_tree/02 最近公共祖先（LCA）、02_ds/07 线段树（含懒标记））
- ✅ [04_tree/05 树上启发式合并](templates\04_tree\05_dsu_on_tree.hpp)（前置：04_tree/04 树链剖分）
- ✅ [04_tree/06 树哈希与树同构](templates\04_tree\06_tree_hash.hpp)（前置：04_tree/01 树的基础：直径、重心、DFS 序）

**数学**

- ✅ [05_math/08 中国剩余定理](templates\05_math\08_crt.hpp)（前置：05_math/02 GCD 与扩展欧几里得）
- ✅ [05_math/09 高斯消元](templates\05_math\09_gauss.hpp)（前置：05_math/07 矩阵与矩阵快速幂）
- ✅ [05_math/10 线性基](templates\05_math\10_linear_basis.hpp)（前置：01_basic/06 位运算）
- ✅ [05_math/11 数论分块（整除分块）](templates\05_math\11_number_block.hpp)
- ✅ [05_math/12 博弈论](templates\05_math\12_game.hpp)（前置：01_basic/06 位运算）
- ⬜ [05_math/17 Lucas 定理与扩展 Lucas](templates\05_math\17_lucas.hpp)（前置：05_math/05 组合数学基础（逆元、组合数））
- ⬜ [05_math/18 阶与原根](templates\05_math\18_primitive_root.hpp)（前置：05_math/04 欧拉函数、05_math/06 快速幂 / 费马小定理）
- ⬜ [05_math/19 卡特兰数与斯特林数](templates\05_math\19_catalan.hpp)（前置：05_math/05 组合数学基础）
- ⬜ [05_math/24 拉格朗日插值](templates\05_math\24_lagrange_interp.hpp)（前置：05_math/04 同余基础、05_math/05 逆元）

**动态规划**

- ✅ [06_dp/06 状压 DP](templates\06_dp\06_bitmask_dp.hpp)（前置：01_basic/06 位运算）
- ✅ [06_dp/07 数位 DP](templates\06_dp\07_digit_dp.hpp)（前置：06_dp/01 线性 DP 入门与记忆化搜索）
- ✅ [06_dp/08 单调队列 / 单调栈优化 DP](templates\06_dp\08_dp_opt_monoqueue.hpp)（前置：02_ds/02 单调队列）
- ✅ [06_dp/09 概率与期望 DP](templates\06_dp\09_dp_expectation.hpp)（前置：06_dp/01 线性 DP 入门与记忆化搜索）

**字符串**

- ✅ [07_string/04 Manacher 最长回文子串](templates\07_string\04_manacher.hpp)（前置：07_string/03 Z 函数（扩展 KMP））
- ✅ [07_string/05 最小表示法](templates\07_string\05_min_repr.hpp)
- ✅ [07_string/06 AC 自动机](templates\07_string\06_ac_automaton.hpp)（前置：02_ds/08 字典树 Trie 与 01-Trie、07_string/02 KMP 与前缀函数）
- ⬜ [07_string/11 序列自动机](templates\07_string\11_seq_automaton.hpp)（前置：07_string/08 后缀自动机（理解自动机思想））

**计算几何**

- ✅ [08_geometry/02 凸包](templates\08_geometry\02_convex_hull.hpp)（前置：08_geometry/01 点、向量与基本运算）
- ✅ [08_geometry/03 旋转卡壳](templates\08_geometry\03_rotating_calipers.hpp)（前置：08_geometry/02 凸包）
- ✅ [08_geometry/04 扫描线：矩形面积并](templates\08_geometry\04_scanline.hpp)（前置：02_ds/07 线段树（含懒标记））
- ✅ [08_geometry/05 平面最近点对](templates\08_geometry\05_closest_pair.hpp)（前置：01_basic/10 分治）
- ⬜ [08_geometry/08 最小圆覆盖](templates\08_geometry\08_min_circle.hpp)（前置：08_geometry/01 二维计算几何基础）

**杂项**

- ✅ [09_misc/03 模拟退火](templates\09_misc\03_simulated_annealing.hpp)（前置：09_misc/01 随机数与防卡哈希）

## 阶段四：高级 ★★★★

**数据结构**

- ✅ [02_ds/15 CDQ 分治与整体二分](templates\02_ds\15_cdq_offline.hpp)（前置：01_basic/10 分治、02_ds/06 树状数组）
- ✅ [02_ds/16 可并堆（左偏树）](templates\02_ds\16_leftist_tree.hpp)（前置：02_ds/03 堆与优先队列）
- ✅ [02_ds/17 Link-Cut Tree](templates\02_ds\17_lct.hpp)（前置：02_ds/12 平衡树、04_tree/04 树链剖分）
- ⬜ [02_ds/19 线段树合并与分裂](templates\02_ds\19_seg_merge_split.hpp)（前置：02_ds/11 线段树进阶、02_ds/13 可持久化数据结构）
- ⬜ [02_ds/20 树套树](templates\02_ds\20_tree_in_tree.hpp)（前置：02_ds/11 线段树进阶、02_ds/12 平衡树）

**图论**

- ✅ [03_graph/12 最小费用最大流](templates\03_graph\12_min_cost_flow.hpp)（前置：03_graph/11 网络流：最大流与最小割）
- ⬜ [03_graph/14 最小树形图（朱刘算法 / Edmonds）](templates\03_graph\14_dmst.hpp)（前置：03_graph/04 最小生成树）
- ⬜ [03_graph/15 上下界网络流](templates\03_graph\15_flow_bound.hpp)（前置：03_graph/11 最大流（Dinic））
- ⬜ [03_graph/16 一般图匹配（带花树 Blossom）](templates\03_graph\16_general_match.hpp)（前置：03_graph/07 二分图匹配（匈牙利 / Hopcroft-Karp））
- ⬜ [03_graph/17 圆方树](templates\03_graph\17_block_forest.hpp)（前置：03_graph/06 Tarjan（割点 / 点双连通分量））

**树**

- ✅ [04_tree/07 点分治](templates\04_tree\07_centroid_decomp.hpp)（前置：04_tree/01 树的基础：直径、重心、DFS 序、01_basic/10 分治）
- ✅ [04_tree/08 虚树](templates\04_tree\08_virtual_tree.hpp)（前置：04_tree/02 最近公共祖先（LCA））
- ⬜ [04_tree/09 动态点分治（点分树）](templates\04_tree\09_dynamic_tree_divide.hpp)（前置：04_tree/07 静态点分治）
- ⬜ [04_tree/10 树上随机游走](templates\04_tree\10_tree_random_walk.hpp)（前置：04_tree/01 树的遍历与直径、05_math/01 概率期望）

**数学**

- ✅ [05_math/13 莫比乌斯反演](templates\05_math\13_mobius.hpp)（前置：05_math/11 数论分块（整除分块）、05_math/06 欧拉函数与欧拉定理）
- ✅ [05_math/14 离散对数 BSGS](templates\05_math\14_bsgs.hpp)（前置：05_math/04 乘法逆元）
- ✅ [05_math/15 Miller-Rabin 与 Pollard-Rho](templates\05_math\15_pollard_rho.hpp)（前置：05_math/03 素数、筛法与分解质因数）
- ✅ [05_math/16 FFT / NTT 多项式乘法](templates\05_math\16_fft_ntt.hpp)（前置：05_math/01 取模运算与快速幂）
- ⬜ [05_math/20 杜教筛](templates\05_math\20_du_sieve.hpp)（前置：05_math/13 线性筛 / 莫比乌斯反演）
- ⬜ [05_math/21 FWT（快速沃尔什变换）](templates\05_math\21_fwt.hpp)（前置：05_math/16 FFT / NTT）
- ⬜ [05_math/22 多项式进阶（牛顿迭代、逆元/开方/ln/exp）](templates\05_math\22_poly_ops.hpp)（前置：05_math/16 FFT / NTT）
- ⬜ [05_math/23 单纯形法（线性规划）](templates\05_math\23_simplex.hpp)（前置：05_math/09 高斯消元）

**动态规划**

- ✅ [06_dp/10 斜率优化与凸包技巧](templates\06_dp\10_dp_opt_slope.hpp)（前置：06_dp/08 单调队列 / 单调栈优化 DP）
- ✅ [06_dp/11 四边形不等式与决策单调性](templates\06_dp\11_dp_opt_quadrangle.hpp)（前置：06_dp/04 区间 DP）
- ⬜ [06_dp/12 插头 DP（轮廓线 DP）](templates\06_dp\12_plug_dp.hpp)（前置：06_dp/06 状态压缩 DP）
- ⬜ [06_dp/13 动态 DP](templates\06_dp\13_dynamic_dp.hpp)（前置：06_dp/05 树形 DP、05_math/07 矩阵乘法 / 矩阵快速幂）
- ⬜ [06_dp/14 DP 套 DP](templates\06_dp\14_dp_of_dp.hpp)（前置：06_dp/06 状态压缩 DP、06_dp/02 线性 DP）
- ⬜ [06_dp/15 WQS 二分与 Slope Trick](templates\06_dp\15_wqs_slope_trick.hpp)（前置：06_dp/10 斜率优化 DP）

**字符串**

- ✅ [07_string/07 后缀数组](templates\07_string\07_suffix_array.hpp)（前置：01_basic/05 排序与离散化）
- ✅ [07_string/08 后缀自动机（SAM）](templates\07_string\08_sam.hpp)（前置：07_string/07 后缀数组）
- ✅ [07_string/09 回文自动机（PAM）](templates\07_string\09_pam.hpp)（前置：07_string/04 Manacher 最长回文子串）
- ⬜ [07_string/10 广义 SAM](templates\07_string\10_general_sam.hpp)（前置：07_string/08 后缀自动机（SAM））

**计算几何**

- ✅ [08_geometry/06 半平面交](templates\08_geometry\06_half_plane.hpp)（前置：08_geometry/01 点、向量与基本运算）
- ⬜ [08_geometry/07 三维几何](templates\08_geometry\07_3d.hpp)（前置：08_geometry/01 二维计算几何基础）
