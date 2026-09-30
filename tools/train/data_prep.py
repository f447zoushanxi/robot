"""
tools/train/data_prep.py

Utility: convert a directory of images and optional label files into
an ultralytics-style dataset layout and produce a data.yaml.

This is intentionally minimal: it moves/copies files into train/val
subdirectories and writes a data.yaml referencing them.

Usage:
  python tools/train/data_prep.py --src /path/to/images --labels /path/to/labels --out data/dataset --val-split 0.1

"""
import argparse
import os
import shutil
import random


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--src', required=True, help='Source images directory')
    p.add_argument('--labels', required=False, help='Optional labels dir in YOLO txt format')
    p.add_argument('--out', required=True, help='Output dataset dir')
    p.add_argument('--val-split', type=float, default=0.1)
    p.add_argument('--classes', nargs='+', default=['bottle','person','trash','clothes'])
    args = p.parse_args()

    imgs = [f for f in os.listdir(args.src) if f.lower().endswith(('.jpg','.jpeg','.png'))]
    random.shuffle(imgs)
    n_val = int(len(imgs) * args.val_split)
    val = set(imgs[:n_val])
    train = imgs[n_val:]

    def ensure(pth):
        if not os.path.exists(pth):
            os.makedirs(pth)

    train_img_dir = os.path.join(args.out, 'images', 'train')
    val_img_dir = os.path.join(args.out, 'images', 'val')
    train_lbl_dir = os.path.join(args.out, 'labels', 'train')
    val_lbl_dir = os.path.join(args.out, 'labels', 'val')
    for d in [train_img_dir, val_img_dir, train_lbl_dir, val_lbl_dir]:
        ensure(d)

    for fn in train:
        shutil.copy(os.path.join(args.src, fn), os.path.join(train_img_dir, fn))
        if args.labels:
            lbl = os.path.splitext(fn)[0] + '.txt'
            src_lbl = os.path.join(args.labels, lbl)
            if os.path.exists(src_lbl):
                shutil.copy(src_lbl, os.path.join(train_lbl_dir, lbl))

    for fn in val:
        shutil.copy(os.path.join(args.src, fn), os.path.join(val_img_dir, fn))
        if args.labels:
            lbl = os.path.splitext(fn)[0] + '.txt'
            src_lbl = os.path.join(args.labels, lbl)
            if os.path.exists(src_lbl):
                shutil.copy(src_lbl, os.path.join(val_lbl_dir, lbl))

    data_yaml = {
        'train': os.path.abspath(train_img_dir),
        'val': os.path.abspath(val_img_dir),
        'nc': len(args.classes),
        'names': args.classes,
    }
    import yaml
    with open(os.path.join(args.out, 'data.yaml'), 'w', encoding='utf-8') as f:
        yaml.dump(data_yaml, f, sort_keys=False)
    print('Prepared dataset at', args.out)

if __name__ == '__main__':
    main()
