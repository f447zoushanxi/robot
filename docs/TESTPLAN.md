# 测试计划（面向家庭递水任务）

## 1. 端到端成功率指标

一次 `deliver_water` 计为成功需同时满足：
1) 语义理解正确（intent+slots）
2) 到达目标区域（导航成功）
3) 抓取动作完成（pick成功）
4) 递交动作完成（hand_over成功）

建议统计：
- E2E 成功率（总成功/总任务）
- 分段成功率（NLU/导航/抓取/递交）
- 平均完成时长与95分位时长

## 2. 数据集制作

### 2.1 ASR 自录集
- 家庭不同房间、不同距离、不同噪声
- 重点口令：`停下`、`记住我的声音`、`记住我`、`我在客厅`、`去厨房`

### 2.2 NLU 标注集
- 意图：`stop/navigate/enroll_owner_voice/enroll_owner/remember_location/deliver_water`
- 槽位：`target/user_location/object`

### 2.3 瓶子图像集
- 搜索区域：厨房台面/餐桌/茶几/地面观察点
- 多光照、遮挡、背景杂乱程度分层采样

### 2.4 身份识别集
- owner 与 guest 各自多轮语音/人脸样本
- 统计：
  - 误识率（guest->owner）
  - 拒识率（owner->unknown/guest）

## 3. 权限策略验证

1. guest 说“停下” -> 必须立即生效
2. guest 说“递水” -> 必须拒绝
3. owner 说“递水” -> 允许执行
4. 首次 enroll 未按物理按钮 -> 拒绝
5. 首次 enroll 在窗口内按下按钮 -> 允许

## 4. 无硬件模式验证

- `robot_base.use_stub=true`，`robot_manipulation.sim_mode=true`
- 启动 `dev_mode.launch.py`，确认节点不因缺失硬件直接崩溃

## 5. 基础构建验证

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
```

## 6. Python 节点启动验证

```bash
cd ros_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
python -m robot_perception.perception_node
```
