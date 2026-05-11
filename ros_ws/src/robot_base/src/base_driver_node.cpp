// Copyright (c) 2026.
// Copyright 2026 f447zoushanxi
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

// =============================================================================
// 模块说明：robot_base — 底盘驱动节点（base_driver_node）
// =============================================================================
// 这个文件是整个机器人底盘（移动平台）的 ROS2 节点入口。
//
// 它的职责：
//   1. 订阅 /cmd_vel（速度指令），把速度发给底盘硬件（无硬件时走 stub 占位）。
//   2. 超时保护：如果超过 cmd_timeout_ms 毫秒没有收到新指令，自动刹车（速度清零）。
//   3. 发布 /odom（里程计，告诉系统机器人走了多远、转了多少角度）。
//   4. 发布 /estop（急停信号，true 表示急停触发，底盘应立刻停下）。
//
// 关键参数（可通过 launch 文件传入）：
//   - use_stub  (bool, 默认 true)：true 表示用模拟底盘，不需要真实硬件。
//   - cmd_timeout_ms (int, 默认 200)：速度指令超时门限，单位毫秒。
//
// 话题（Topics）：
//   - 订阅 /cmd_vel              [geometry_msgs/Twist]  接收速度指令
//   - 发布 /odom                 [nav_msgs/Odometry]    发布里程计
//   - 发布 /estop                [std_msgs/Bool]        发布急停状态
// =============================================================================

#include <chrono>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "robot_base/safety_utils.hpp"
#include "std_msgs/msg/bool.hpp"

// std::chrono_literals 让我们可以写 50ms、1s 这样直观的时间量
using namespace std::chrono_literals;

// BaseDriverNode 继承自 rclcpp::Node，即它是一个 ROS2 节点
// 想象成：Node 是积木的基座，BaseDriverNode 在上面搭建了底盘驱动的功能
class BaseDriverNode : public rclcpp::Node
{
public:
  // 构造函数：节点启动时自动执行，完成参数读取、话题注册、定时器创建等初始化工作
  BaseDriverNode()
  : Node("base_driver_node")  // 告诉 ROS2 这个节点叫 "base_driver_node"
  {
    // 读取 ROS2 参数，如果 launch 文件没有传入则使用括号里的默认值
    use_stub_ = declare_parameter<bool>("use_stub", true);
    timeout_ms_ = declare_parameter<int>("cmd_timeout_ms", 200);

    // 订阅 /cmd_vel，收到速度指令后记录指令内容和收到时间
    // 第二个参数 10 是"队列深度"——最多缓存 10 条消息，超出会丢弃最旧的
    cmd_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10,
      [this](const geometry_msgs::msg::Twist::SharedPtr msg) {
        // 保存最新的速度指令
        last_cmd_ = *msg;
        // 记录收到指令的时刻，用于后续超时检测
        last_cmd_time_ = now();
      });

    // 创建发布者：向 /odom 发布里程计，向 /estop 发布急停状态
    odom_pub_ = create_publisher<nav_msgs::msg::Odometry>("/odom", 10);
    estop_pub_ = create_publisher<std_msgs::msg::Bool>("/estop", 10);

    // 每 50ms（即 20Hz）定时调用一次 on_timer()，处理超时检测和数据发布
    timer_ = create_wall_timer(50ms, std::bind(&BaseDriverNode::on_timer, this));

    RCLCPP_INFO(
      get_logger(),
      "robot_base started (stub=%s). Serial protocol and real IO are intentionally placeholders.",
      use_stub_ ? "true" : "false");
  }

private:
  // on_timer：每 50ms 被定时器调用一次
  // 主要工作：检测超时→应用刹车→发布里程计→发布急停状态
  void on_timer()
  {
    const auto now_time = now();

    // 超时检测：当前时间 - 上次收到指令时间 > 超时门限（转换成纳秒比较）
    // 如果超时，说明上游（executor）已经停止发送指令，应立刻停车
    const bool timeout = (now_time - last_cmd_time_).nanoseconds() >
      (static_cast<int64_t>(timeout_ms_) * 1000000LL);

    // 如果超时，apply_timeout_brake 会把速度强制清零；否则原样返回
    const geometry_msgs::msg::Twist safe_cmd = robot_base::apply_timeout_brake(last_cmd_, timeout);

    // 构造并发布里程计消息
    // stub 模式下，odom.twist 直接使用安全速度指令（真实底盘应读编码器计算）
    nav_msgs::msg::Odometry odom;
    odom.header.stamp = now_time;     // 时间戳
    odom.header.frame_id = "odom";    // 坐标系：世界坐标系（原点）
    odom.child_frame_id = "base_link";  // 机器人本体坐标系
    odom.twist.twist = safe_cmd;
    odom_pub_->publish(odom);

    // 发布急停状态：stub 模式下永远为 false（不触发急停）
    // 真实底盘会从 MCU 读取急停按钮状态
    std_msgs::msg::Bool estop;
    estop.data = false;
    estop_pub_->publish(estop);
  }

  // --- 成员变量 ---
  bool use_stub_{true};          // 是否使用模拟底盘（无硬件时保持 true）
  int timeout_ms_{200};          // 速度指令超时门限，单位毫秒
  rclcpp::Time last_cmd_time_{0, 0, RCL_ROS_TIME};  // 上次收到速度指令的时刻
  geometry_msgs::msg::Twist last_cmd_{};             // 最新速度指令

  // --- ROS2 通信对象 ---
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr estop_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

// main：程序入口，每个 ROS2 可执行节点都有且只有一个 main
int main(int argc, char ** argv)
{
  // 初始化 ROS2 通信基础设施
  rclcpp::init(argc, argv);
  // 创建节点并进入事件循环（spin），直到节点被关闭
  rclcpp::spin(std::make_shared<BaseDriverNode>());
  // 清理 ROS2 资源
  rclcpp::shutdown();
  return 0;
}
