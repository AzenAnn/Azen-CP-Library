/**
 * 01_basic/01 快读快写与比赛骨架
 * 难度：★ 入门（约 CF 800–1300）
 * 前置：无
 * 状态：DONE（已实现，tests/ 中有对应测试）
 *
 * 【学习顺序】
 *   1. 关闭同步 ios::sync_with_stdio(false)
 *   2. getchar 快读 / 快写
 *   3. __int128 的输入输出
 *   4. 多组数据的写法与清空
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/contest/io/
 *   灵神模板(Go)   https://github.com/EndlessCheng/codeforces-go/blob/master/copypasta/io.go
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *   https://www.luogu.com.cn/problem/P1001  入门  P1001 A+B Problem  熟悉提交格式
 *   https://www.luogu.com.cn/problem/P1089  入门  P1089 [NOIP 2004 提高组] 津津的储蓄计划  多行输入与模拟
 *   https://www.luogu.com.cn/problem/P1401  入门  P1401 [入门赛 #18] 禁止在 int 乘 int 时不开 long long  乘法溢出，开 long long
 *   https://www.luogu.com.cn/problem/P5708  入门  P5708 【深基2.习2】三角形面积  浮点数与保留小数输出
 *   https://codeforces.com/problemset/problem/1352/A  CF800  CF1352A Sum of Round Numbers  多组数据
 *   https://codeforces.com/problemset/problem/1873/A  CF800  CF1873A Short Sort  多组数据 + 字符串
 *   https://codeforces.com/problemset/problem/4/A  CF800  CF4A Watermelon  读入与判断
 *   https://codeforces.com/problemset/problem/71/A  CF800  CF71A Way Too Long Words  读字符串
 *   https://www.luogu.com.cn/problem/P10815  普及−  P10815 【模板】快速读入  1e7 级输入，getchar 快读
 *   https://codeforces.com/problemset/problem/1/A  CF1000  CF1A Theatre Square  答案超 int，开 long long
 *   https://codeforces.com/problemset/problem/375/B  CF1600  CF375B Maximum Submatrix 2  5000×5000 的 01 矩阵输入，需快读
 *
 */

// 用法一（绝大多数题够用）：在 main 开头写
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
// 关同步后不要再混用 scanf/printf/getchar 与 cin/cout；
// 换行用 '\n' 而不是 endl（endl 每次都会刷新缓冲区，输出多时很慢）。

// 用法二：输入量在 1e6 以上、时限很紧时，用 getchar 快读（此时不要再用 cin）
template <class T>
void read(T &x) {
    x = 0;
    bool neg = false;
    int c = getchar();
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    if (c == '-') neg = true, c = getchar();
    // 负数直接往负方向累加，读入类型的最小值（如 LLONG_MIN）也不会溢出
    while (c >= '0' && c <= '9') x = neg ? x * 10 - (c - '0') : x * 10 + (c - '0'), c = getchar();
}

// 快写：能正确输出类型的最小值（如 LLONG_MIN）
template <class T>
void write(T x) {
    char buf[45];
    int n = 0;
    bool neg = x < 0;
    do {
        int d = int(x % 10);
        buf[n++] = char('0' + (d < 0 ? -d : d));
        x /= 10;
    } while (x);
    if (neg) putchar('-');
    while (n) putchar(buf[--n]);
}

// __int128 不能直接用 cin/cout，用上面的 read / write 即可（T = __int128）。
// 多组数据：每组开始时把全局数组、容器清空，只清用到的前 n 个，不要每组 memset 整个大数组。
