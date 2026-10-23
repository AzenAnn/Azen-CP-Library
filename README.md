<div align="center">

# Azen-CP-Library

**一个"边学边攒"的 C++ 算法竞赛模板库**

每个知识点一个文件：学习路线 + 资料链接 + 我的笔记 + 题单 + 经过对拍测试的模板代码，全都在一起。

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![GNU G++](https://img.shields.io/badge/compiler-GNU%20G%2B%2B-3b915d)
![tests](https://img.shields.io/badge/tests-ASan%20%2B%20UBSan%20%2B%20GLIBCXX__DEBUG-6b7280)
![ICPC / CCPC / OI](https://img.shields.io/badge/for-ICPC%20%7C%20CCPC%20%7C%20OI%20%7C%20Codeforces-orange)

[快速开始](#-快速开始) · [学习路线](ROADMAP.md) · [全部专题](#-全部专题) · [比赛时怎么用](#-比赛时怎么用) · [维护流程](#-日常维护)

</div>

---

## ✨ 特点

- **编号就是学习顺序**：`02_ds/07_segment_tree.hpp` 是数据结构专题的第 7 个知识点，按编号从小到大学即可；跨专题的依赖写在每个文件头的"前置"里。
- **学、练、用一体**：文件头是学习路线和题单，文件下方是能直接粘贴的模板代码，一个文件就是一个知识点的全部。
- **每个模板都有对拍测试**：`tests/` 里用随机小数据和暴力解法逐一对比，在 AddressSanitizer、UBSan、`_GLIBCXX_DEBUG` 下运行。
- **题单都核对过**：洛谷、Codeforces 的题按难度排好序，每题附一句话提示，链接、题名、难度都逐题核对过。
- **线上线下都能用**：线上赛 `#include` 一个总头文件或者直接复制；现场赛用 `tools/make_pdf.py` 生成打印版。
- 维护方式参考了灵茶山艾府的 [codeforces-go](https://github.com/EndlessCheng/codeforces-go)。

## 📚 内容一览

| 目录 | 内容 |
|---|---|
| `01_basic` 基础算法 | 前缀和与差分、二分与三分、双指针、离散化、位运算、贪心、高精度、倍增、分治、构造、搜索、01 分数规划 |
| `02_ds` 数据结构 | 单调栈 / 队列、堆、并查集、ST 表、树状数组、线段树（懒标记、动态开点、吉司机、线段树分治）、笛卡尔树、分块、莫队、平衡树、可持久化、珂朵莉树、CDQ、左偏树、LCT、李超树、KD-Tree |
| `03_graph` 图论 | 最短路、最小环与次短路、最小生成树、矩阵树定理、SCC、割点与桥、二分图、KM、差分约束、2-SAT、欧拉路、网络流、费用流、最小割树、K 短路、朱刘算法、上下界网络流、带花树、圆方树、支配树 |
| `04_tree` 树 | 直径与重心、LCA、树上差分、基环树、重链剖分、长链剖分、dsu on tree、树哈希、Prüfer 序列、点分治、虚树、点分树 |
| `05_math` 数学 | 取模与快速幂、GCD、筛法、逆元、组合数、康托展开 / 错排 / 约瑟夫、欧拉函数、矩阵、CRT、高斯消元、线性基、整除分块、博弈、莫比乌斯反演、BSGS、Pollard-Rho、FFT/NTT、Lucas、原根、卡特兰 / 斯特林、二项式反演、Burnside/Pólya、杜教筛、FWT、多项式、单纯形、拉格朗日插值 |
| `06_dp` 动态规划 | 线性、LIS/LCS、背包、区间、树形与换根、状压、数位、单调队列 / 斜率 / 四边形不等式优化、期望、插头 DP、斯坦纳树、动态 DP、DP 套 DP、WQS 二分 |
| `07_string` 字符串 | 字符串哈希、KMP、Z 函数、Manacher、最小表示法、AC 自动机、后缀数组、SAM、PAM、广义 SAM、序列自动机 |
| `08_geometry` 计算几何 | 点与向量、凸包、旋转卡壳、扫描线、最近点对、半平面交、圆的基本计算、自适应 Simpson、三维几何、最小圆覆盖 |
| `09_misc` 杂项 | 随机化与防卡哈希、交互题、模拟退火、折半搜索 |

完成情况和每个专题的链接见下方的 [全部专题](#-全部专题)；按难度分成四个阶段的学习路线见 [ROADMAP.md](ROADMAP.md)。

## 🚀 快速开始

复制 [contest/starter.cpp](contest/starter.cpp)，引入总头文件 [templates/all.hpp](templates/all.hpp)，就能直接用库里全部已完成的模板（总头文件已包含万能头、`using namespace std` 以及 `ll`、`ull`、`pii`）：

```cpp
#include "../templates/all.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Fenwick f(5);
    f.add(1, 10);
    cout << f.sum(1, 5) << '\n';   // 10

    DSU d(5);
    d.merge(0, 1);
    cout << d.same(0, 1) << '\n';  // 1
}
```

- 路径相对于当前 `.cpp` 文件，上面的写法适用于 `contest/` 下的文件；[contest/example.cpp](contest/example.cpp) 是完整示例。
- OJ 访问不到本地的 `templates/`，提交前要把用到的模板展开成源码（每个模板都能单独复制粘贴）。
- 新增模板或把状态改成 `DONE` 后，运行 `python tools/gen_all.py` 更新总头文件，再运行 `bash tools/test_all.sh all_headers` 检查。

## 🧩 模板文件长什么样

每个 `templates/**/*.hpp` 都是同样的格式（例如 [templates/02_ds/07_segment_tree.hpp](templates/02_ds/07_segment_tree.hpp)）：

```cpp
/**
 * 02_ds/07 线段树（含懒标记）      ← 编号与标题
 * 难度：★★ 提高（约 CF 1300–1900）
 * 前置：02_ds/06 树状数组
 * 状态：DONE / TODO / NOTE         ← 已实现并测试 / 待自己实现 / 没有固定模板
 *
 * 【学习顺序】     本知识点拆成的小步骤
 * 【学习资料】     OI-wiki、cp-algorithms、灵神模板的对应页面
 * 【模板题】       用来验证自己实现的模板题
 * 【我的笔记】     学完后用自己的话写：直观理解、易错点
 * 【题单】         链接  难度  一句话提示（按难度排序）
 */
（模板代码）
```

**代码约定**

- C++17；所有模板都假设开头是 `#include <bits/stdc++.h>`、`using namespace std;`、`using ll = long long;`。
- 每个模板都能直接复制粘贴，不依赖其他模板（计算几何的模板需要先粘贴 `08_geometry/01`）。
- 下标从 0 还是从 1 开始、区间开闭，都写在模板的注释里；多数是"从 0 开始"，树状数组按惯例从 1 开始。
- 递归深度可能很大的地方（树、图）尽量用 BFS 序或显式栈代替递归。

**难度星级**（大致对应 Codeforces 分数）：★ 入门 800–1300 · ★★ 提高 1300–1900 · ★★★ 进阶 1900–2400 · ★★★★ 高级 2400+。
排序参考了 [OI-wiki](https://oi-wiki.org/) 的目录、[cp-algorithms](https://cp-algorithms.com/)、[USACO Guide](https://usaco.guide/) 的分级和灵神题单的难度顺序。

## 🏁 比赛时怎么用

```bash
cd contest
cp starter.cpp a.cpp         # 每题复制一份骨架
# 把样例存到 samples/1.in、samples/1.out ……
./run.sh a.cpp               # 编译（带越界、溢出检查）并比对所有样例
FAST=1 ./run.sh a.cpp        # 不带检查，跑得更快
cd stress && ./stress.sh     # 对拍：gen.cpp 生成数据，brute.cpp 暴力，sol.cpp 正解
```

- 代码里可以用 `debug(x, vec, mp)` 打印变量，只在本地 `-DLOCAL` 时生效，提交时自动失效。
- 现场赛打印：`python3 tools/make_pdf.py`（加 `--compact` 去掉注释）生成 `build/cp-library.pdf`，只包含状态为 DONE 的模板。

<details>
<summary>Windows / VS Code 下的用法</summary>

我本地的 VS Code 设置（`.vscode/` 不上传）把 Code Runner 的 C++ 运行命令固定到 `C:\1mingw\mingw64\bin\g++.exe`（GCC 13.2），使用 C++20，点击 Run Code 即可。PowerShell 中也可以在仓库根目录运行：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/run_cpp.ps1 contest/starter.cpp
```

脚本把程序编译到源文件所在目录的 `bin/`，编译失败时不会运行旧程序。注意本机 PATH 中的 `g++` 实际位于 LLVM-MinGW 目录，直接把 `clang++` 改为 `g++` 仍不等于使用上述 GCC；本库的 `__lg` 和 PBDS 需要 GNU 标准库扩展。

</details>

## ✅ 测试

```bash
bash tools/test_all.sh            # 编译并运行 tests/ 下的全部测试（Linux 下开启 ASan / UBSan / _GLIBCXX_DEBUG）
bash tools/test_all.sh 02_ds      # 只测某个专题，也可以写文件名的一部分，如 segment_tree
```

每个 `DONE` 模板在 `tests/` 里都有一个对拍测试：随机生成小数据，用模板和暴力解法分别计算，结果必须完全一致。

## 🔧 日常维护

**每做完一道题**：题解存到 `solutions/` 对应目录；有新技巧就把"链接 + 难度 + 一句话提示"补进对应模板的【题单】。

**学完一个 TODO 专题**：按【学习顺序】学、在【我的笔记】里写理解 → 在文件下方写出实现、在 `tests/` 里写对拍 → `tools/test_all.sh 专题名` 通过后把状态改成 DONE → 去 AC 【模板题】。

**新增模板**：`python3 tools/new_template.py 07_string lyndon "Lyndon 分解" --level 4 --prereq "07_string/05"`，会生成带标准文件头的模板和测试骨架。

**改完后**：

```bash
bash tools/test_all.sh            # 所有测试都要通过
python3 tools/gen_index.py        # 更新下面的目录和 ROADMAP.md
python3 tools/gen_all.py          # 更新总头文件 templates/all.hpp
git add -A && git commit -m "segment_tree: 新增区间赋值标记；题单 +3"
```

## 🗂️ 目录结构

```
Azen-CP-Library/
├── templates/     模板，按专题分目录，编号即学习顺序；all.hpp 为总头文件
├── tests/         每个已完成模板的对拍测试
├── contest/       比赛工具：starter.cpp 骨架、debug.hpp、run.sh 跑样例、stress/ 对拍
├── solutions/     题解（按平台存放，命名规则见 solutions/README.md）
├── tools/         test_all.sh、gen_index.py、gen_all.py、new_template.py、make_pdf.py
├── ROADMAP.md     按难度分阶段的学习路线（自动生成）
└── README.md      本文件（下方目录自动生成）
```

## 📑 全部专题

以下内容由 `python3 tools/gen_index.py` 自动生成。

<!-- INDEX:START -->

共 **140** 个专题：✅ 已完成 133，⬜ 待实现 0，📝 笔记 7；题单中已收录 **1686** 道题。

| 专题 | 已完成 | 待实现 | 笔记 | 题单 | 进度 |
|---|:---:|:---:|:---:|:---:|---|
| [01_basic 基础算法](#01_basic) | 8 | 0 | 5 | 187 | ██████████ |
| [02_ds 数据结构](#02_ds) | 24 | 0 | 0 | 316 | ██████████ |
| [03_graph 图论](#03_graph) | 22 | 0 | 0 | 233 | ██████████ |
| [04_tree 树](#04_tree) | 13 | 0 | 0 | 155 | ██████████ |
| [05_math 数学](#05_math) | 27 | 0 | 0 | 313 | ██████████ |
| [06_dp 动态规划](#06_dp) | 15 | 0 | 1 | 204 | ██████████ |
| [07_string 字符串](#07_string) | 11 | 0 | 0 | 133 | ██████████ |
| [08_geometry 计算几何](#08_geometry) | 10 | 0 | 0 | 92 | ██████████ |
| [09_misc 杂项](#09_misc) | 3 | 0 | 1 | 53 | ██████████ |

<a id="01_basic"></a>

### 01_basic 基础算法（8/13）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [快读快写与比赛骨架](templates/01_basic/01_io.hpp) | ★ | 无 | ✅ 已完成 | 11 |
| 02 | [前缀和与差分](templates/01_basic/02_prefix_sum.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 03 | [二分查找、二分答案与三分](templates/01_basic/03_binary_search.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [双指针与滑动窗口](templates/01_basic/04_two_pointers.hpp) | ★ | 01_basic/02 前缀和与差分 | ✅ 已完成 | 15 |
| 05 | [排序与离散化](templates/01_basic/05_sort_discrete.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 06 | [位运算](templates/01_basic/06_bits.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 07 | [贪心常见模型](templates/01_basic/07_greedy.hpp) | ★ | 无 | 📝 笔记 | 15 |
| 08 | [高精度](templates/01_basic/08_bignum.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 09 | [倍增](templates/01_basic/09_binary_lifting.hpp) | ★★ | 01_basic/03 二分查找、二分答案与三分 | 📝 笔记 | 15 |
| 10 | [分治](templates/01_basic/10_divide_conquer.hpp) | ★★ | 01_basic/05 排序与离散化 | 📝 笔记 | 15 |
| 11 | [构造](templates/01_basic/11_construction.hpp) | ★★ | 无 | 📝 笔记 | 15 |
| 12 | [搜索：DFS、BFS、剪枝](templates/01_basic/12_search.hpp) | ★★ | 01_basic/10 分治 | 📝 笔记 | 14 |
| 13 | [01 分数规划](templates/01_basic/13_frac_programming.hpp) | ★★★ | 01_basic/03 二分查找、二分答案与三分、01_basic/07 贪心常见模型 | ✅ 已完成 | 12 |

<a id="02_ds"></a>

### 02_ds 数据结构（24/24）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [栈与单调栈](templates/02_ds/01_stack_monotone.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 02 | [单调队列](templates/02_ds/02_monotone_queue.hpp) | ★ | 02_ds/01 栈与单调栈 | ✅ 已完成 | 15 |
| 03 | [堆与优先队列](templates/02_ds/03_heap.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [并查集](templates/02_ds/04_dsu.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 05 | [ST 表](templates/02_ds/05_sparse_table.hpp) | ★★ | 01_basic/09 倍增 | ✅ 已完成 | 15 |
| 06 | [树状数组](templates/02_ds/06_fenwick.hpp) | ★★ | 01_basic/02 前缀和与差分、01_basic/06 位运算 | ✅ 已完成 | 15 |
| 07 | [线段树（含懒标记）](templates/02_ds/07_segment_tree.hpp) | ★★ | 02_ds/06 树状数组 | ✅ 已完成 | 15 |
| 08 | [字典树 Trie 与 01-Trie](templates/02_ds/08_trie.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 09 | [笛卡尔树](templates/02_ds/09_cartesian_tree.hpp) | ★★★ | 02_ds/01 栈与单调栈、02_ds/05 ST 表 | ✅ 已完成 | 9 |
| 10 | [分块与根号分治](templates/02_ds/10_sqrt_decomposition.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 11 | [莫队](templates/02_ds/11_mo.hpp) | ★★★ | 02_ds/10 分块与根号分治 | ✅ 已完成 | 15 |
| 12 | [线段树进阶](templates/02_ds/12_segment_tree_adv.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 13 | [吉司机线段树（区间最值操作）](templates/02_ds/13_segment_tree_beats.hpp) | ★★★★ | 02_ds/07 线段树（含懒标记）、02_ds/12 线段树进阶 | ✅ 已完成 | 8 |
| 14 | [平衡树](templates/02_ds/14_balanced_tree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 15 | [可持久化数据结构](templates/02_ds/15_persistent.hpp) | ★★★ | 02_ds/12 线段树进阶、02_ds/08 字典树 Trie 与 01-Trie | ✅ 已完成 | 15 |
| 16 | [珂朵莉树（ODT）](templates/02_ds/16_odt.hpp) | ★★★ | 02_ds/14 平衡树 | ✅ 已完成 | 15 |
| 17 | [CDQ 分治与整体二分](templates/02_ds/17_cdq_offline.hpp) | ★★★★ | 01_basic/10 分治、02_ds/06 树状数组 | ✅ 已完成 | 15 |
| 18 | [线段树分治（离线删边）](templates/02_ds/18_segment_tree_divide.hpp) | ★★★ | 02_ds/04 并查集、02_ds/07 线段树（含懒标记） | ✅ 已完成 | 7 |
| 19 | [可并堆（左偏树）](templates/02_ds/19_leftist_tree.hpp) | ★★★★ | 02_ds/03 堆与优先队列 | ✅ 已完成 | 12 |
| 20 | [Link-Cut Tree](templates/02_ds/20_lct.hpp) | ★★★★ | 02_ds/14 平衡树、04_tree/05 树链剖分 | ✅ 已完成 | 15 |
| 21 | [李超线段树](templates/02_ds/21_li_chao_tree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 10 |
| 22 | [线段树合并与分裂](templates/02_ds/22_seg_merge_split.hpp) | ★★★★ | 02_ds/12 线段树进阶、02_ds/15 可持久化数据结构 | ✅ 已完成 | 11 |
| 23 | [树套树](templates/02_ds/23_tree_in_tree.hpp) | ★★★★ | 02_ds/12 线段树进阶、02_ds/14 平衡树 | ✅ 已完成 | 9 |
| 24 | [K-D Tree](templates/02_ds/24_kdtree.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 10 |

<a id="03_graph"></a>

### 03_graph 图论（22/22）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [存图与图的遍历](templates/03_graph/01_graph_basic.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 02 | [拓扑排序](templates/03_graph/02_topo.hpp) | ★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 03 | [最短路](templates/03_graph/03_shortest_path.hpp) | ★★ | 03_graph/01 存图与图的遍历、02_ds/03 堆与优先队列 | ✅ 已完成 | 15 |
| 04 | [最小环与次短路](templates/03_graph/04_min_cycle.hpp) | ★★ | 03_graph/03 最短路 | ✅ 已完成 | 6 |
| 05 | [最小生成树](templates/03_graph/05_mst.hpp) | ★★ | 02_ds/04 并查集 | ✅ 已完成 | 15 |
| 06 | [矩阵树定理（生成树计数）](templates/03_graph/06_matrix_tree.hpp) | ★★★★ | 03_graph/05 最小生成树、05_math/10 高斯消元 | ✅ 已完成 | 8 |
| 07 | [强连通分量与缩点](templates/03_graph/07_scc.hpp) | ★★ | 03_graph/02 拓扑排序 | ✅ 已完成 | 15 |
| 08 | [割点、桥与双连通分量](templates/03_graph/08_bcc.hpp) | ★★★ | 03_graph/07 强连通分量与缩点 | ✅ 已完成 | 15 |
| 09 | [二分图](templates/03_graph/09_bipartite.hpp) | ★★★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 10 | [二分图最大权匹配（KM / 匈牙利算法）](templates/03_graph/10_km.hpp) | ★★★★ | 03_graph/09 二分图 | ✅ 已完成 | 6 |
| 11 | [差分约束](templates/03_graph/11_diff_constraints.hpp) | ★★★ | 03_graph/03 最短路 | ✅ 已完成 | 15 |
| 12 | [2-SAT](templates/03_graph/12_two_sat.hpp) | ★★★ | 03_graph/07 强连通分量与缩点 | ✅ 已完成 | 15 |
| 13 | [欧拉路径与欧拉回路](templates/03_graph/13_euler.hpp) | ★★★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 14 | [网络流：最大流与最小割](templates/03_graph/14_max_flow.hpp) | ★★★ | 03_graph/03 最短路 | ✅ 已完成 | 15 |
| 15 | [最小费用最大流](templates/03_graph/15_min_cost_flow.hpp) | ★★★★ | 03_graph/14 网络流：最大流与最小割 | ✅ 已完成 | 15 |
| 16 | [最小割树（Gomory-Hu Tree）](templates/03_graph/16_gomory_hu.hpp) | ★★★★ | 03_graph/14 网络流：最大流与最小割 | ✅ 已完成 | 5 |
| 17 | [K 短路](templates/03_graph/17_kth_path.hpp) | ★★★ | 03_graph/03 最短路 | ✅ 已完成 | 4 |
| 18 | [最小树形图（朱刘算法 / Edmonds）](templates/03_graph/18_dmst.hpp) | ★★★★ | 03_graph/05 最小生成树 | ✅ 已完成 | 3 |
| 19 | [上下界网络流](templates/03_graph/19_flow_bound.hpp) | ★★★★ | 03_graph/14 网络流：最大流与最小割 | ✅ 已完成 | 6 |
| 20 | [一般图匹配（带花树 Blossom）](templates/03_graph/20_general_match.hpp) | ★★★★ | 03_graph/09 二分图 | ✅ 已完成 | 2 |
| 21 | [圆方树](templates/03_graph/21_block_forest.hpp) | ★★★★ | 03_graph/08 割点、桥与双连通分量 | ✅ 已完成 | 10 |
| 22 | [支配树](templates/03_graph/22_dominator_tree.hpp) | ★★★★ | 03_graph/02 拓扑排序、04_tree/02 最近公共祖先（LCA） | ✅ 已完成 | 3 |

<a id="04_tree"></a>

### 04_tree 树（13/13）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [树的基础：直径、重心、DFS 序](templates/04_tree/01_tree_basic.hpp) | ★ | 03_graph/01 存图与图的遍历 | ✅ 已完成 | 15 |
| 02 | [最近公共祖先（LCA）](templates/04_tree/02_lca.hpp) | ★★ | 04_tree/01 树的基础：直径、重心、DFS 序、01_basic/09 倍增 | ✅ 已完成 | 15 |
| 03 | [树上差分与树上前缀和](templates/04_tree/03_tree_diff.hpp) | ★★ | 04_tree/02 最近公共祖先（LCA）、01_basic/02 前缀和与差分 | ✅ 已完成 | 13 |
| 04 | [基环树](templates/04_tree/04_pseudo_tree.hpp) | ★★★ | 04_tree/01 树的基础：直径、重心、DFS 序、06_dp/05 树形 DP 与换根 DP、02_ds/02 单调队列 | ✅ 已完成 | 11 |
| 05 | [树链剖分](templates/04_tree/05_hld.hpp) | ★★★ | 04_tree/02 最近公共祖先（LCA）、02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 06 | [长链剖分](templates/04_tree/06_long_chain.hpp) | ★★★★ | 04_tree/05 树链剖分、01_basic/09 倍增 | ✅ 已完成 | 6 |
| 07 | [树上启发式合并](templates/04_tree/07_dsu_on_tree.hpp) | ★★★ | 04_tree/05 树链剖分 | ✅ 已完成 | 15 |
| 08 | [树哈希与树同构](templates/04_tree/08_tree_hash.hpp) | ★★★ | 04_tree/01 树的基础：直径、重心、DFS 序 | ✅ 已完成 | 15 |
| 09 | [Prüfer 序列](templates/04_tree/09_prufer.hpp) | ★★★ | 04_tree/01 树的基础：直径、重心、DFS 序、05_math/05 组合数与计数原理 | ✅ 已完成 | 9 |
| 10 | [点分治](templates/04_tree/10_centroid_decomp.hpp) | ★★★★ | 04_tree/01 树的基础：直径、重心、DFS 序、01_basic/10 分治 | ✅ 已完成 | 15 |
| 11 | [虚树](templates/04_tree/11_virtual_tree.hpp) | ★★★★ | 04_tree/02 最近公共祖先（LCA） | ✅ 已完成 | 15 |
| 12 | [动态点分治（点分树）](templates/04_tree/12_dynamic_tree_divide.hpp) | ★★★★ | 04_tree/10 点分治 | ✅ 已完成 | 6 |
| 13 | [树上随机游走](templates/04_tree/13_tree_random_walk.hpp) | ★★★★ | 04_tree/01 树的基础：直径、重心、DFS 序、06_dp/09 概率与期望 DP | ✅ 已完成 | 5 |

<a id="05_math"></a>

### 05_math 数学（27/27）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [取模运算与快速幂](templates/05_math/01_modint.hpp) | ★ | 无 | ✅ 已完成 | 11 |
| 02 | [GCD 与扩展欧几里得](templates/05_math/02_gcd.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 03 | [素数、筛法与分解质因数](templates/05_math/03_prime_sieve.hpp) | ★ | 无 | ✅ 已完成 | 15 |
| 04 | [乘法逆元](templates/05_math/04_inverse.hpp) | ★★ | 05_math/01 取模运算与快速幂、05_math/02 GCD 与扩展欧几里得 | ✅ 已完成 | 15 |
| 05 | [组合数与计数原理](templates/05_math/05_combinatorics.hpp) | ★★ | 05_math/04 乘法逆元 | ✅ 已完成 | 15 |
| 06 | [康托展开、错排与约瑟夫问题](templates/05_math/06_perm_counting.hpp) | ★★ | 05_math/05 组合数与计数原理、02_ds/06 树状数组 | ✅ 已完成 | 10 |
| 07 | [欧拉函数与欧拉定理](templates/05_math/07_euler_phi.hpp) | ★★ | 05_math/03 素数、筛法与分解质因数 | ✅ 已完成 | 15 |
| 08 | [矩阵与矩阵快速幂](templates/05_math/08_matrix.hpp) | ★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 09 | [中国剩余定理](templates/05_math/09_crt.hpp) | ★★★ | 05_math/02 GCD 与扩展欧几里得 | ✅ 已完成 | 15 |
| 10 | [高斯消元](templates/05_math/10_gauss.hpp) | ★★★ | 05_math/08 矩阵与矩阵快速幂 | ✅ 已完成 | 15 |
| 11 | [线性基](templates/05_math/11_linear_basis.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 12 | [数论分块（整除分块）](templates/05_math/12_number_block.hpp) | ★★★ | 无 | ✅ 已完成 | 15 |
| 13 | [博弈论](templates/05_math/13_game.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 14 | [莫比乌斯反演](templates/05_math/14_mobius.hpp) | ★★★★ | 05_math/12 数论分块（整除分块）、05_math/07 欧拉函数与欧拉定理 | ✅ 已完成 | 15 |
| 15 | [离散对数 BSGS](templates/05_math/15_bsgs.hpp) | ★★★★ | 05_math/04 乘法逆元 | ✅ 已完成 | 13 |
| 16 | [Miller-Rabin 与 Pollard-Rho](templates/05_math/16_pollard_rho.hpp) | ★★★★ | 05_math/03 素数、筛法与分解质因数 | ✅ 已完成 | 8 |
| 17 | [FFT / NTT 多项式乘法](templates/05_math/17_fft_ntt.hpp) | ★★★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 18 | [Lucas 定理与扩展 Lucas](templates/05_math/18_lucas.hpp) | ★★★ | 05_math/05 组合数与计数原理 | ✅ 已完成 | 9 |
| 19 | [阶与原根](templates/05_math/19_primitive_root.hpp) | ★★★ | 05_math/07 欧拉函数与欧拉定理、05_math/01 取模运算与快速幂 | ✅ 已完成 | 7 |
| 20 | [卡特兰数与斯特林数](templates/05_math/20_catalan.hpp) | ★★★ | 05_math/05 组合数与计数原理 | ✅ 已完成 | 12 |
| 21 | [二项式反演](templates/05_math/21_binomial_inversion.hpp) | ★★★ | 05_math/05 组合数与计数原理、05_math/06 康托展开、错排与约瑟夫问题 | ✅ 已完成 | 6 |
| 22 | [Burnside 引理与 Pólya 定理](templates/05_math/22_burnside_polya.hpp) | ★★★★ | 05_math/07 欧拉函数与欧拉定理、05_math/04 乘法逆元 | ✅ 已完成 | 7 |
| 23 | [杜教筛](templates/05_math/23_du_sieve.hpp) | ★★★★ | 05_math/14 莫比乌斯反演 | ✅ 已完成 | 6 |
| 24 | [FWT（快速沃尔什变换）](templates/05_math/24_fwt.hpp) | ★★★★ | 05_math/17 FFT / NTT 多项式乘法 | ✅ 已完成 | 9 |
| 25 | [多项式进阶（牛顿迭代、逆元/开方/ln/exp）](templates/05_math/25_poly_ops.hpp) | ★★★★ | 05_math/17 FFT / NTT 多项式乘法 | ✅ 已完成 | 8 |
| 26 | [单纯形法（线性规划）](templates/05_math/26_simplex.hpp) | ★★★★ | 05_math/10 高斯消元 | ✅ 已完成 | 5 |
| 27 | [拉格朗日插值](templates/05_math/27_lagrange_interp.hpp) | ★★★ | 05_math/02 GCD 与扩展欧几里得、05_math/04 乘法逆元 | ✅ 已完成 | 7 |

<a id="06_dp"></a>

### 06_dp 动态规划（15/16）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [线性 DP 入门与记忆化搜索](templates/06_dp/01_dp_basic.hpp) | ★ | 无 | 📝 笔记 | 15 |
| 02 | [LIS、LCS 与编辑距离](templates/06_dp/02_lis_lcs.hpp) | ★ | 06_dp/01 线性 DP 入门与记忆化搜索、01_basic/03 二分查找、二分答案与三分 | ✅ 已完成 | 13 |
| 03 | [背包 DP](templates/06_dp/03_knapsack.hpp) | ★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 04 | [区间 DP](templates/06_dp/04_interval_dp.hpp) | ★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 05 | [树形 DP 与换根 DP](templates/06_dp/05_tree_dp.hpp) | ★★ | 04_tree/01 树的基础：直径、重心、DFS 序 | ✅ 已完成 | 15 |
| 06 | [状压 DP](templates/06_dp/06_bitmask_dp.hpp) | ★★★ | 01_basic/06 位运算 | ✅ 已完成 | 15 |
| 07 | [数位 DP](templates/06_dp/07_digit_dp.hpp) | ★★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 08 | [单调队列 / 单调栈优化 DP](templates/06_dp/08_dp_opt_monoqueue.hpp) | ★★★ | 02_ds/02 单调队列 | ✅ 已完成 | 15 |
| 09 | [概率与期望 DP](templates/06_dp/09_dp_expectation.hpp) | ★★★ | 06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 15 |
| 10 | [斜率优化与凸包技巧](templates/06_dp/10_dp_opt_slope.hpp) | ★★★★ | 06_dp/08 单调队列 / 单调栈优化 DP | ✅ 已完成 | 15 |
| 11 | [四边形不等式与决策单调性](templates/06_dp/11_dp_opt_quadrangle.hpp) | ★★★★ | 06_dp/04 区间 DP | ✅ 已完成 | 15 |
| 12 | [插头 DP（轮廓线 DP）](templates/06_dp/12_plug_dp.hpp) | ★★★★ | 06_dp/06 状压 DP | ✅ 已完成 | 9 |
| 13 | [最小斯坦纳树](templates/06_dp/13_steiner_tree.hpp) | ★★★★ | 06_dp/06 状压 DP、03_graph/03 最短路 | ✅ 已完成 | 4 |
| 14 | [动态 DP](templates/06_dp/14_dynamic_dp.hpp) | ★★★★ | 06_dp/05 树形 DP 与换根 DP、05_math/08 矩阵与矩阵快速幂 | ✅ 已完成 | 8 |
| 15 | [DP 套 DP](templates/06_dp/15_dp_of_dp.hpp) | ★★★★ | 06_dp/06 状压 DP、06_dp/01 线性 DP 入门与记忆化搜索 | ✅ 已完成 | 6 |
| 16 | [WQS 二分与 Slope Trick](templates/06_dp/16_wqs_slope_trick.hpp) | ★★★★ | 06_dp/10 斜率优化与凸包技巧 | ✅ 已完成 | 14 |

<a id="07_string"></a>

### 07_string 字符串（11/11）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [字符串哈希](templates/07_string/01_string_hash.hpp) | ★★ | 05_math/01 取模运算与快速幂 | ✅ 已完成 | 15 |
| 02 | [KMP 与前缀函数](templates/07_string/02_kmp.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 03 | [Z 函数（扩展 KMP）](templates/07_string/03_z_function.hpp) | ★★ | 07_string/02 KMP 与前缀函数 | ✅ 已完成 | 11 |
| 04 | [Manacher 最长回文子串](templates/07_string/04_manacher.hpp) | ★★★ | 07_string/03 Z 函数（扩展 KMP） | ✅ 已完成 | 15 |
| 05 | [最小表示法](templates/07_string/05_min_repr.hpp) | ★★★ | 无 | ✅ 已完成 | 6 |
| 06 | [AC 自动机](templates/07_string/06_ac_automaton.hpp) | ★★★ | 02_ds/08 字典树 Trie 与 01-Trie、07_string/02 KMP 与前缀函数 | ✅ 已完成 | 15 |
| 07 | [后缀数组](templates/07_string/07_suffix_array.hpp) | ★★★★ | 01_basic/05 排序与离散化 | ✅ 已完成 | 15 |
| 08 | [后缀自动机（SAM）](templates/07_string/08_sam.hpp) | ★★★★ | 07_string/07 后缀数组 | ✅ 已完成 | 15 |
| 09 | [回文自动机（PAM）](templates/07_string/09_pam.hpp) | ★★★★ | 07_string/04 Manacher 最长回文子串 | ✅ 已完成 | 12 |
| 10 | [广义 SAM](templates/07_string/10_general_sam.hpp) | ★★★★ | 07_string/08 后缀自动机（SAM） | ✅ 已完成 | 9 |
| 11 | [序列自动机](templates/07_string/11_seq_automaton.hpp) | ★★★ | 07_string/08 后缀自动机（SAM） | ✅ 已完成 | 5 |

<a id="08_geometry"></a>

### 08_geometry 计算几何（10/10）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [点、向量与基本运算](templates/08_geometry/01_geo_basic.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 02 | [凸包](templates/08_geometry/02_convex_hull.hpp) | ★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 15 |
| 03 | [旋转卡壳](templates/08_geometry/03_rotating_calipers.hpp) | ★★★ | 08_geometry/02 凸包 | ✅ 已完成 | 11 |
| 04 | [扫描线：矩形面积并](templates/08_geometry/04_scanline.hpp) | ★★★ | 02_ds/07 线段树（含懒标记） | ✅ 已完成 | 15 |
| 05 | [平面最近点对](templates/08_geometry/05_closest_pair.hpp) | ★★★ | 01_basic/10 分治 | ✅ 已完成 | 8 |
| 06 | [半平面交](templates/08_geometry/06_half_plane.hpp) | ★★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 11 |
| 07 | [圆的基本计算](templates/08_geometry/07_circle.hpp) | ★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 6 |
| 08 | [自适应 Simpson 积分](templates/08_geometry/08_simpson.hpp) | ★★★ | 08_geometry/07 圆的基本计算 | ✅ 已完成 | 4 |
| 09 | [三维几何](templates/08_geometry/09_3d.hpp) | ★★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 4 |
| 10 | [最小圆覆盖](templates/08_geometry/10_min_circle.hpp) | ★★★ | 08_geometry/01 点、向量与基本运算 | ✅ 已完成 | 3 |

<a id="09_misc"></a>

### 09_misc 杂项（3/4）

| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |
|---|---|---|---|---|---|
| 01 | [随机数与防卡哈希](templates/09_misc/01_random_hash.hpp) | ★★ | 无 | ✅ 已完成 | 15 |
| 02 | [交互题](templates/09_misc/02_interactive.hpp) | ★★ | 01_basic/03 二分查找、二分答案与三分 | 📝 笔记 | 15 |
| 03 | [模拟退火](templates/09_misc/03_simulated_annealing.hpp) | ★★★ | 09_misc/01 随机数与防卡哈希 | ✅ 已完成 | 15 |
| 04 | [折半搜索 / Meet in the Middle](templates/09_misc/04_meet_in_middle.hpp) | ★★ | 01_basic/03 二分查找、二分答案与三分、01_basic/12 搜索：DFS、BFS、剪枝 | ✅ 已完成 | 8 |

<!-- INDEX:END -->

## 参考与致谢

- 维护方式和题单写法参考了 [EndlessCheng/codeforces-go](https://github.com/EndlessCheng/codeforces-go)（MIT 协议），本库的代码是独立编写的 C++ 实现，没有复制其中的代码。
- 学习资料：[OI-wiki](https://oi-wiki.org/)、[cp-algorithms](https://cp-algorithms.com/)、[USACO Guide](https://usaco.guide/)。
- 验证用的题目：[洛谷](https://www.luogu.com.cn/)、[Library Checker](https://judge.yosupo.jp/)。
