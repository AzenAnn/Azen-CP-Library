#!/usr/bin/env python3
"""新建一个模板文件（带标准文件头）和对应的测试文件骨架。
用法：
  python3 tools/new_template.py 专题目录 文件名 "标题" [--level 1-4] [--prereq "02_ds/07, 01_basic/03"] [--num 编号]
例：
  python3 tools/new_template.py 02_ds segment_tree_beats "吉司机线段树" --level 4 --prereq "02_ds/07"
不写 --num 时自动取该专题的下一个编号。想插到中间时，可以用 07a 这样的编号，排序时会排在 07 之后。"""
import argparse
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LEVEL = {1: '★ 入门（约 CF 800–1300）', 2: '★★ 提高（约 CF 1300–1900）',
         3: '★★★ 进阶（约 CF 1900–2400）', 4: '★★★★ 高级（约 CF 2400+）'}

ap = argparse.ArgumentParser()
ap.add_argument('topic')
ap.add_argument('slug')
ap.add_argument('title')
ap.add_argument('--level', type=int, default=2, choices=[1, 2, 3, 4])
ap.add_argument('--prereq', default='')
ap.add_argument('--num', default='')
a = ap.parse_args()

tdir = os.path.join(ROOT, 'templates', a.topic)
os.makedirs(tdir, exist_ok=True)
nums = [f.split('_')[0] for f in os.listdir(tdir) if f.endswith('.hpp')]
num = a.num or '%02d' % (max([int(n) for n in nums if n.isdigit()] or [0]) + 1)
rel = f'{a.topic}/{num}_{a.slug}'
path = os.path.join(ROOT, 'templates', rel + '.hpp')
if os.path.exists(path):
    raise SystemExit(f'{path} 已存在')


def title_of(code):   # "02_ds/07" -> 该文件的标题
    d, n = code.split('/')
    for f in os.listdir(os.path.join(ROOT, 'templates', d)):
        if f.startswith(n + '_'):
            return open(os.path.join(ROOT, 'templates', d, f), encoding='utf-8').read().splitlines()[1].split(None, 2)[-1]
    return ''


pre = [p.strip() for p in a.prereq.split(',') if p.strip()]
pre_text = '、'.join(f'{p} {title_of(p)}' for p in pre) if pre else '无'
header = f'''/**
 * {a.topic}/{num} {a.title}
 * 难度：{LEVEL[a.level]}
 * 前置：{pre_text}
 * 状态：TODO（待自己实现：学完后写在下方，并在 tests/ 中写测试）
 *
 * 【学习顺序】
 *   1.
 *
 * 【学习资料】
 *   OI-wiki        https://oi-wiki.org/
 *   cp-algorithms  https://cp-algorithms.com/
 *
 * 【模板题 / 入门题】
 *
 * 【我的笔记】（学完后用自己的话写：直观理解、易错点、和其他算法的联系）
 *
 * 【题单】（按难度排序，做一道补一道。格式：链接  难度  一句话提示）
 *
 */

// TODO：在这里写出实现
'''
open(path, 'w', encoding='utf-8').write(header)
test = os.path.join(ROOT, 'tests', rel + '.test.cpp')
os.makedirs(os.path.dirname(test), exist_ok=True)
if not os.path.exists(test):
    open(test, 'w', encoding='utf-8').write(f'''#include "../common.hpp"
#include "../../templates/{rel}.hpp"

int main() {{
    for (int it = 0; it < 500; it++) {{
        // 1. 随机生成小数据  2. 用模板计算  3. 用暴力计算  4. CHECK(两者相等)
    }}
    return 0;
}}
''')
print('已创建', os.path.relpath(path, ROOT))
print('已创建', os.path.relpath(test, ROOT))
print('写完后运行 tools/test_all.sh，再运行 python3 tools/gen_index.py 更新目录')
