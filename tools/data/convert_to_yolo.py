"""
tools/data/convert_to_yolo.py

Convert a COCO-style annotations.json into YOLOv5/YOLOv8 label txt files.
This script requires pycocotools. It's a minimal converter for bbox-only annotations.
"""
import argparse
import json
import os

try:
    from pycocotools.coco import COCO
except Exception:
    COCO = None


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--coco', required=True, help='path to annotations JSON')
    p.add_argument('--imgdir', required=True, help='path to images')
    p.add_argument('--out', required=True, help='output dir for labels')
    args = p.parse_args()

    if COCO is None:
        print('pycocotools not installed. Install with pip install pycocotools')
        return
    coco = COCO(args.coco)
    anns = coco.loadAnns(coco.getAnnIds())
    os.makedirs(args.out, exist_ok=True)
    for img in coco.dataset['images']:
        img_id = img['id']
        filename = img['file_name']
        w = img['width']; h = img['height']
        ann_ids = coco.getAnnIds(imgIds=[img_id])
        out_lines = []
        for aid in ann_ids:
            a = coco.loadAnns(aid)[0]
            if 'bbox' in a:
                x,y,boxw,boxh = a['bbox']
                # convert to yolo normalized cx cy w h
                cx = (x + boxw/2)/w
                cy = (y + boxh/2)/h
                nw = boxw/w
                nh = boxh/h
                cls = a.get('category_id',0)
                out_lines.append(f"{cls} {cx} {cy} {nw} {nh}\n")
        if out_lines:
            base = os.path.splitext(filename)[0]
            with open(os.path.join(args.out, base+'.txt'),'w',encoding='utf-8') as f:
                f.writelines(out_lines)
    print('Converted COCO -> YOLO labels at', args.out)

if __name__ == '__main__':
    main()
