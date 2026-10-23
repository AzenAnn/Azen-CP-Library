#!/usr/bin/env python3
"""扫描 templates/ 下所有模板的文件头，生成 README.md 中的目录和 ROADMAP.md（按难度分阶段的学习路线）。
用法：python3 tools/gen_index.py
新增、改名、修改文件头中的难度 / 前置 / 状态，或往题单里加题后，运行一次即可。"""
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOPIC_NAMES = {
    '01_basic': '基础算法', '02_ds': '数据结构', '03_graph': '图论', '04_tree': '树',
    '05_math': '数学', '06_dp': '动态规划', '07_string': '字符串', '08_geometry': '计算几何', '09_misc': '杂项',
}
STATUS_MARK = {'DONE': '✅ 已完成', 'TODO': '⬜ 待实现', 'NOTE': '📝 笔记'}
LEVEL_NAMES = {1: '阶段一：入门 ★', 2: '阶段二：提高 ★★', 3: '阶段三：进阶 ★★★', 4: '阶段四：高级 ★★★★'}


def parse(path):
    text = open(path, encoding='utf-8').read()
    head = text.split('*/', 1)[0]
    lines = [l.strip().lstrip('*').strip() for l in head.splitlines()]
    info = {'path': os.path.relpath(path, ROOT).replace(os.sep, '/'), 'title': '', 'level': 0, 'prereq': '无', 'status': '?', 'problems': 0}
    m = re.match(r'(\S+)\s+(.*)', lines[1]) if len(lines) > 1 else None
    if m:
        info['code'], info['title'] = m.group(1), m.group(2)
    section = ''
    for l in lines:
        if l.startswith('难度：'):
            info['level'] = l.count('★')
            info['level_text'] = l[3:]
        elif l.startswith('前置：'):
            info['prereq'] = l[3:]
        elif l.startswith('状态：'):
            info['status'] = l[3:].split('（')[0].strip()
        elif l.startswith('【'):
            section = l
        elif section.startswith('【题单】') and l.startswith('http'):
            info['problems'] += 1
    return info


def collect():
    topics = []
    tdir = os.path.join(ROOT, 'templates')
    for d in sorted(os.listdir(tdir)):
        if not os.path.isdir(os.path.join(tdir, d)):
            continue
        items = [parse(os.path.join(tdir, d, f)) for f in sorted(os.listdir(os.path.join(tdir, d))) if f.endswith('.hpp')]
        if not items:   # 空目录（如 00_languages）不列出
            continue
        topics.append((d, TOPIC_NAMES.get(d, d), items))
    return topics


def stars(n):
    return '★' * n if n else '?'


def main():
    topics = collect()
    allitems = [it for _, _, items in topics for it in items]
    cnt = {s: sum(1 for it in allitems if it['status'] == s) for s in STATUS_MARK}
    probs = sum(it['problems'] for it in allitems)
    out = ['', f'共 **{len(allitems)}** 个专题：✅ 已完成 {cnt["DONE"]}，⬜ 待实现 {cnt["TODO"]}，📝 笔记 {cnt["NOTE"]}；题单中已收录 **{probs}** 道题。', '',
           '| 专题 | 已完成 | 待实现 | 笔记 | 题单 | 进度 |', '|---|:---:|:---:|:---:|:---:|---|']
    for d, name, items in topics:
        c = {s: sum(1 for it in items if it['status'] == s) for s in STATUS_MARK}
        p = sum(it['problems'] for it in items)
        filled = round(10 * (c['DONE'] + c['NOTE']) / len(items))
        out.append(f'| [{d} {name}](#{d}) | {c["DONE"]} | {c["TODO"]} | {c["NOTE"]} | {p} | {"█" * filled}{"░" * (10 - filled)} |')
    out.append('')
    for d, name, items in topics:
        done = sum(1 for it in items if it['status'] == 'DONE')
        out += [f'<a id="{d}"></a>', '', f'### {d} {name}（{done}/{len(items)}）', '', '| 编号 | 内容 | 难度 | 前置 | 状态 | 题单 |', '|---|---|---|---|---|---|']
        for it in items:
            num = os.path.basename(it['path']).split('_')[0]
            out.append(f'| {num} | [{it["title"]}]({it["path"]}) | {stars(it["level"])} | {it["prereq"]} | {STATUS_MARK.get(it["status"], it["status"])} | {it["problems"]} |')
        out.append('')
    readme = os.path.join(ROOT, 'README.md')
    text = open(readme, encoding='utf-8').read()
    start, end = '<!-- INDEX:START -->', '<!-- INDEX:END -->'
    if start in text and end in text:
        text = text.split(start)[0] + start + '\n' + '\n'.join(out) + '\n' + end + text.split(end)[1]
        open(readme, 'w', encoding='utf-8').write(text)
        print('已更新 README.md 目录')
    else:
        print('README.md 中没有找到目录标记，跳过')

    road = ['# 学习路线（按难度分阶段）', '',
            '本文件由 `python3 tools/gen_index.py` 自动生成，请不要手动修改。',
            '', '同一阶段内建议各专题交替推进：每学完一个知识点，就去做它的模板题和题单里的题。'
            '括号中的"前置"表示学这一项之前最好先掌握的内容。',
            '', '图标：✅ 模板代码已实现并通过测试　⬜ 待自己实现　📝 没有固定模板，以笔记和题单为主', '']
    for lv in (1, 2, 3, 4):
        road += [f'## {LEVEL_NAMES[lv]}', '']
        for d, name, items in topics:
            sel = [it for it in items if it['level'] == lv]
            if not sel:
                continue
            road.append(f'**{name}**')
            road.append('')
            for it in sel:
                mark = {'DONE': '✅', 'NOTE': '📝'}.get(it['status'], '⬜')
                pre = '' if it['prereq'] == '无' else f'（前置：{it["prereq"]}）'
                road.append(f'- {mark} [{it["code"]} {it["title"]}]({it["path"]}){pre}')
            road.append('')
    open(os.path.join(ROOT, 'ROADMAP.md'), 'w', encoding='utf-8').write('\n'.join(road))
    print('已生成 ROADMAP.md')


if __name__ == '__main__':
    main()
