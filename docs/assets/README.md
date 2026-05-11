# docs/assets — 截图与媒体资源目录

本目录存放项目文档所需的截图和其他媒体文件。

---

## 如何生成 RViz 渲染截图

按照 [RENDERING.md](../RENDERING.md) 的步骤启动仿真并打开 RViz，然后：

### 方式 A：RViz 内置导出

在 RViz 菜单栏：**File → Export → Screenshot…**

建议保存路径：
```
docs/assets/robot_render.png
```

### 方式 B：系统截图工具

按 `PrtSc`（Print Screen）键截图，然后裁剪到 RViz 窗口区域。

### 方式 C：命令行截图（需安装 scrot）

```bash
sudo apt-get install scrot
# 启动 RViz 后等待 5 秒再截图
sleep 5 && scrot docs/assets/robot_render.png -u
```

---

## 截图命名规范

| 文件名 | 说明 |
|--------|------|
| `robot_render.png` | RViz 机器人模型渲染截图（主要交付物）|
| `tf_tree.png` | TF 坐标树截图（可选）|
| `rviz_laserscan.png` | 激光扫描显示截图（可选）|

---

## 注意

- 截图文件不会被 Git 追踪（已在 `.gitignore` 中排除 `*.png`）。
- 如需将截图提交到仓库，请先确认文件大小合理（建议 < 500 KB）。
- CI 环境没有显示器，截图只能在本地生成。
