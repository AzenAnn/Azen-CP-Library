#!/usr/bin/env python3
"""生成包含全部 DONE 模板的总头文件：python tools/gen_all.py。"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    headers = []
    for path in sorted((ROOT / "templates").glob("*/*.hpp")):
        source = path.read_text(encoding="utf-8-sig")
        head = source.split("*/", 1)[0]
        if re.search(r"状态：\s*DONE\b", head):
            headers.append(path.relative_to(ROOT / "templates"))

    lines = [
        "// 自动生成：python tools/gen_all.py；新增 DONE 模板后重新运行。",
        f"// 共 {len(headers)} 个已实现模板，面向 GNU C++17 单文件竞赛程序。",
        "// 在 contest/*.cpp 中使用：#include \"../templates/all.hpp\"",
        "// 已包含标准库和类型别名；无需再次引入各专题头文件。",
        "#pragma once",
        "",
        "#include <bits/stdc++.h>",
        "using namespace std;",
        "using ll = long long;",
        "using ull = unsigned long long;",
        "using pii = pair<int, int>;",
    ]
    previous_topic = None
    for path in headers:
        if path.parent.name != previous_topic:
            previous_topic = path.parent.name
            lines.extend(["", f"// {previous_topic}"])
        lines.append(f'#include "{path.as_posix()}"')
    (ROOT / "templates/all.hpp").write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"Generated templates/all.hpp: {len(headers)} DONE headers")


if __name__ == "__main__":
    main()
