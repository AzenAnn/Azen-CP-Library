#!/usr/bin/env bash
# 对拍：不断生成随机数据，比较 sol 和 brute 的输出，直到发现不同或跑满 N 次
#   ./stress.sh          默认跑 1000 次
#   ./stress.sh 5000
# 发现错误时，出错的数据保存在 bin/fail.in，两边的输出在 bin/sol.out 和 bin/brute.out
set -u
cd "$(dirname "$0")"
N=${1:-1000}
mkdir -p bin
# 本机 PATH 里 /usr/bin/g++ 可能是 WSL 的（会编出 Linux ELF），优先用 Windows 版 g++
CXX=${CXX:-/c/1mingw/mingw64/bin/g++.exe}
for f in gen brute sol; do
    "$CXX" -std=c++17 -O2 -o bin/$f $f.cpp || { echo "$f.cpp 编译失败"; exit 1; }
done
for ((i = 1; i <= N; i++)); do
    bin/gen $i > bin/in.txt
    bin/sol < bin/in.txt > bin/sol.out 2>/dev/null
    bin/brute < bin/in.txt > bin/brute.out 2>/dev/null
    if ! diff -bB bin/sol.out bin/brute.out >/dev/null; then
        cp bin/in.txt bin/fail.in
        echo "第 $i 组数据（种子 $i）结果不同！"
        echo "--- 输入 ---"; cat bin/in.txt
        echo "--- sol ---"; cat bin/sol.out
        echo "--- brute ---"; cat bin/brute.out
        exit 1
    fi
    ((i % 100 == 0)) && echo "已通过 $i 组"
done
echo "全部 $N 组一致 ✓"
