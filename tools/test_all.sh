#!/usr/bin/env bash
# 编译并运行 tests/ 下的所有测试（Linux 下带 AddressSanitizer / UBSan / _GLIBCXX_DEBUG 检查）
# 用法：bash tools/test_all.sh            运行全部测试
#       bash tools/test_all.sh 02_ds      只运行某个专题（或任意路径片段，如 segment_tree）
set -u
cd "$(dirname "$0")/.."
filter=${1:-}
mkdir -p build/tests
# 本机 PATH 里 /usr/bin/g++ 可能是 WSL 的（会编出 Linux ELF）。优先用 Windows 版 g++，
# 可用环境变量 CXX 覆盖，如 CXX=clang++ bash tools/test_all.sh
CXX=${CXX:-/c/1mingw/mingw64/bin/g++.exe}
CXXFLAGS="-std=c++17 -O1 -g -Wall -Wextra -Wno-unused-function"
# sanitizer 只在 Linux 下开启（MinGW/clang for Windows 链接不上或运行崩溃）
if [ "$(uname -s)" = Linux ]; then
    CXXFLAGS="$CXXFLAGS -fsanitize=address,undefined -fno-sanitize-recover=all -D_GLIBCXX_DEBUG"
fi

run_one() {
    t=$1
    name=${t#tests/}; name=${name%.test.cpp}
    bin="build/tests/${name//\//__}"
    log="$bin.log"
    if ! "$CXX" $CXXFLAGS "$t" -o "$bin" >"$log" 2>&1; then
        echo "FAIL  $name  （编译失败，见 $log）"; return
    fi
    if timeout 120 "$bin" >>"$log" 2>&1; then
        echo "PASS  $name"
    else
        echo "FAIL  $name  （运行失败，见 $log）"
    fi
}
export -f run_one
export CXXFLAGS
export CXX

find tests -name '*.test.cpp' | grep -- "$filter" | sort | xargs -P "$(nproc)" -I{} bash -c 'run_one {}' | sort -k2 > build/tests/result.txt
cat build/tests/result.txt
pass=$(grep -c '^PASS' build/tests/result.txt)
fail=$(grep -c '^FAIL' build/tests/result.txt)
echo "------"
echo "通过 $pass 个，失败 $fail 个"

# 检查：状态为 DONE 的模板是否都有测试
for f in templates/*/*.hpp; do
    rel=${f#templates/}; rel=${rel%.hpp}
    if grep -q '状态：DONE' "$f" && [ ! -f "tests/$rel.test.cpp" ]; then
        echo "提醒：$f 状态为 DONE，但没有 tests/$rel.test.cpp"
    fi
done
[ "$fail" -eq 0 ]
