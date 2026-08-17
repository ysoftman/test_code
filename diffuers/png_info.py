#!/usr/bin/env python3
"""Print PNG size/mode and embedded text metadata. Usage: png_info.py [--json] [-k KEY]... <file.png>..."""

import argparse
import json

from PIL import Image

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("files", nargs="+")
parser.add_argument("-j", "--json", action="store_true", help="output as JSON")
parser.add_argument(
    "-k",
    "--key",
    action="append",
    default=[],
    help="only show these metadata keys (repeatable)",
)
args = parser.parse_args()

results = []
for path in args.files:
    with Image.open(path) as im:
        text = getattr(im, "text", {})
        if args.key:
            text = {k: v for k, v in text.items() if k in args.key}
        results.append(
            {
                "path": path,
                "width": im.width,
                "height": im.height,
                "mode": im.mode,
                "text": text,
            }
        )

if args.json:
    print(json.dumps(results, ensure_ascii=False, indent=2))
else:
    for r in results:
        print(f"{r['path']}: {r['width']}x{r['height']} {r['mode']}")
        for key, value in r["text"].items():
            print(f"  {key}: {value}")
