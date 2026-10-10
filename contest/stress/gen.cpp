// 随机数据生成器：./gen 种子  >  输入文件
// 示例题：给出 T 组数组，求每组的最大子段和。换题时改这里，生成小数据，方便暴力跑得动
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv) {
    mt19937_64 rng(argc > 1 ? atoll(argv[1]) : 0);
    auto rnd = [&](long long l, long long r) { return (long long)(rng() % (r - l + 1)) + l; };
    int T = rnd(1, 3);
    cout << T << '\n';
    while (T--) {
        int n = rnd(1, 8);
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << rnd(-10, 10) << " \n"[i == n - 1];
    }
}
