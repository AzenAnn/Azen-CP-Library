#!/usr/bin/env python3
"""把所有状态为 DONE 的模板合成一份可打印的资料（现场赛用），输出 build/cp-library.html 和 build/cp-library.pdf。
用法：python3 tools/make_pdf.py            保留代码中的注释
      python3 tools/make_pdf.py --compact  去掉整行注释，页数更少
文件头的长注释（学习资料、笔记、题单）不会打印，只保留标题。"""
import html
import os
import re
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
compact = '--compact' in sys.argv
parts = []
toc = []
for d in sorted(os.listdir(os.path.join(ROOT, 'templates'))):
    full = os.path.join(ROOT, 'templates', d)
    if not os.path.isdir(full):
        continue
    for f in sorted(os.listdir(full)):
        if not f.endswith('.hpp'):
            continue
        text = open(os.path.join(full, f), encoding='utf-8').read()
        if '状态：DONE' not in text.split('*/', 1)[0]:
            continue
        title = text.splitlines()[1].lstrip(' *')
        code = text.split('*/', 1)[1].strip('\n')
        if compact:
            code = '\n'.join(l for l in code.splitlines() if not l.strip().startswith('//'))
            code = re.sub(r'\n{3,}', '\n\n', code)
        esc = html.escape(code)
        esc = re.sub(r'(//.*)', r'<span class="c">\1</span>', esc)   # 注释显示为灰色
        toc.append(title)
        parts.append(f'<section><h2>{html.escape(title)}</h2><pre>{esc}</pre></section>')

page = f'''<!doctype html><html><head><meta charset="utf-8"><title>cp-library</title><style>
@page {{ size: A4; margin: 10mm 8mm; }}
body {{ font-family: "Noto Sans CJK SC", "Microsoft YaHei", sans-serif; font-size: 7.5pt; column-count: 2; column-gap: 6mm; column-rule: 0.3pt solid #999; }}
h1 {{ column-span: all; font-size: 13pt; margin: 0 0 2mm; }}
.toc {{ column-span: all; font-size: 7.5pt; margin-bottom: 3mm; }}
h2 {{ font-size: 8.5pt; margin: 2mm 0 1mm; background: #eee; padding: 0.5mm 1mm; break-after: avoid; }}
pre {{ font-family: "DejaVu Sans Mono", Consolas, monospace; font-size: 6.8pt; line-height: 1.22; margin: 0; white-space: pre-wrap; word-break: break-all; }}
.c {{ color: #666; }}
</style></head><body><h1>cp-library 算法竞赛模板</h1>
<div class="toc">{" · ".join(html.escape(t) for t in toc)}</div>
{"".join(parts)}</body></html>'''
os.makedirs(os.path.join(ROOT, 'build'), exist_ok=True)
out_html = os.path.join(ROOT, 'build', 'cp-library.html')
open(out_html, 'w', encoding='utf-8').write(page)
print(f'已生成 {os.path.relpath(out_html, ROOT)}（{len(toc)} 个模板）')
chrome = next((shutil.which(c) for c in ['google-chrome', 'chromium', 'chromium-browser'] if shutil.which(c)), None)
if chrome:
    out_pdf = os.path.join(ROOT, 'build', 'cp-library.pdf')
    subprocess.run([chrome, '--headless', '--disable-gpu', '--no-sandbox', '--no-pdf-header-footer',
                    f'--print-to-pdf={out_pdf}', 'file://' + out_html], stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL)
    print('已生成', os.path.relpath(out_pdf, ROOT))
else:
    print('没有找到 Chrome：可以用浏览器打开 HTML 文件，再"打印 → 另存为 PDF"')
