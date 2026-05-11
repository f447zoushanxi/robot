#!/usr/bin/env python3
# Copyright (c) 2026.
#
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# 工具：validate_rviz_config.py — 非 GUI 验证 RViz 配置文件
# =============================================================================
# 这个脚本在 CI 环境（没有显示器）中验证 RViz 配置文件：
#   1. 文件存在
#   2. Fixed Frame 使用正确的坐标系（odom）
#   3. 必要的显示插件已启用（RobotModel、TF、LaserScan）
#   4. 话题订阅了正确的名称（/scan、/odom、/robot_description）
#
# 用法：
#   python3 tools/validate_rviz_config.py
#
# 退出码：
#   0 = 验证通过
#   1 = 验证失败（错误信息会打印到 stdout）
# =============================================================================

import sys
from pathlib import Path

# ──────────────────────────────────────────────────────────────────────────────
# 配置：要验证的 RViz 文件路径（相对于仓库根目录）
# ──────────────────────────────────────────────────────────────────────────────
REPO_ROOT = Path(__file__).resolve().parent.parent
RVIZ_FILE = REPO_ROOT / 'ros_ws' / 'src' / 'robot_bringup' / 'rviz' / 'dev_view.rviz'

# 期望的 Fixed Frame（RViz 视图的参考坐标系）
EXPECTED_FIXED_FRAME = 'odom'

# 期望存在的显示类名（RViz 插件）
REQUIRED_CLASSES = [
    'rviz_default_plugins/RobotModel',
    'rviz_default_plugins/TF',
    'rviz_default_plugins/LaserScan',
]

# 期望订阅的话题（在 RViz 配置文件里以 Value: /xxx 形式出现）
REQUIRED_TOPICS = [
    '/robot_description',  # RobotModel 的描述话题
    '/scan',               # LaserScan 话题
    '/odom',               # Odometry 话题
]


def main() -> int:
    errors = []

    # 1. 检查文件是否存在
    if not RVIZ_FILE.exists():
        print(f'[FAIL] RViz 配置文件不存在: {RVIZ_FILE}')
        return 1

    content = RVIZ_FILE.read_text(encoding='utf-8')
    print(f'[OK]   RViz 配置文件存在: {RVIZ_FILE}')

    # 2. 检查 Fixed Frame
    if f'Fixed Frame: {EXPECTED_FIXED_FRAME}' in content:
        print(f'[OK]   Fixed Frame = {EXPECTED_FIXED_FRAME!r}')
    else:
        errors.append(
            f'Fixed Frame 不是 {EXPECTED_FIXED_FRAME!r}（应使用 odom 作为参考坐标系）'
        )

    # 3. 检查必要的显示类
    for cls in REQUIRED_CLASSES:
        if f'Class: {cls}' in content:
            print(f'[OK]   Display class 已启用: {cls}')
        else:
            errors.append(f'缺少 Display class: {cls}')

    # 4. 检查话题订阅
    for topic in REQUIRED_TOPICS:
        if f'Value: {topic}' in content:
            print(f'[OK]   话题已配置: {topic}')
        else:
            errors.append(f'缺少话题配置: {topic}')

    # 输出结果
    if errors:
        print()
        print('[FAIL] RViz 配置验证失败：')
        for err in errors:
            print(f'  ✗ {err}')
        return 1

    print()
    print('[PASS] RViz 配置文件验证通过！')
    return 0


if __name__ == '__main__':
    sys.exit(main())
