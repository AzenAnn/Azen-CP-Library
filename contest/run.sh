#!/usr/bin/env bash
# 比赛时用：编译并用 samples/ 中的样例测试（PowerShell / cmd 下要用 bash run.sh，./run.sh 只会打开文件）
#   bash run.sh              编译 main.cpp，依次运行 samples/*.in，与同名 .out 比较（忽略行末空格和空行）
#   bash run.sh a.cpp        换成别的源文件
#   FAST=1 bash run.sh       不加 sanitizer，编译更快、运行更快（数据大时用）
#   bash run.sh main.cpp -   不跑样例，直接从键盘输入
# 样例文件放在 samples/ 下：1.in 1.out 2.in 2.out ……
set -u
cd "$(dirname "$0")"
src=${1:-main.cpp}
mkdir -p bin
# 本机 PATH 里 /usr/bin/g++ 是 WSL 的，会编出 Linux ELF，Windows 下跑不了。
# 优先用 Windows 版 g++（可用环境变量 CXX 覆盖，如 CXX=clang++ ./run.sh）
CXX=${CXX:-/c/1mingw/mingw64/bin/g++.exe}
flags="-std=c++17 -O2 -Wall -Wextra -Wshadow -DLOCAL"
# sanitizer 在 Windows（MinGW/clang）下链接不上或跑不起来，只有 Linux 下默认开启
if [ "${FAST:-0}" != 1 ] && [ "$(uname -s)" = Linux ]; then
    flags="$flags -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
fi
bin="bin/$(basename "${src%.cpp}")"
"$CXX" $flags "$src" -o "$bin" || { echo "编译失败"; exit 1; }

if [ "${2:-}" = "-" ] || ! ls samples/*.in >/dev/null 2>&1; then
    "$bin"; exit
fi
pass=0; total=0
for in in samples/*.in; do
    exp=${in%.in}.out
    total=$((total + 1))
    start=$(date +%s%N)
    got=$(timeout 10 "$bin" < "$in"); code=$?
    ms=$(( ($(date +%s%N) - start) / 1000000 ))
    if [ $code -ne 0 ]; then
        echo "✗ $in  运行错误（返回值 $code，${ms}ms）"
    elif [ ! -f "$exp" ]; then
        echo "? $in  没有 $exp，输出为："; echo "$got"
    elif diff -bB <(echo "$got") "$exp" >/dev/null; then
        echo "✓ $in  (${ms}ms)"; pass=$((pass + 1))
    else
        echo "✗ $in  答案错误 (${ms}ms)"
        diff -bB --side-by-side --width=80 <(echo "$got") "$exp" | head -30
        echo "  （左边是你的输出，右边是标准答案）"
    fi
done
echo "通过 $pass / $total"
