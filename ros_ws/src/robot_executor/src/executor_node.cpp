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
// 模块说明：robot_executor — 任务执行器节点（executor_node）
// =============================================================================
// 这是整个机器人任务编排的"大脑"节点，负责把"递水"等高层命令分解成
// 一步一步的子任务，并按顺序驱动机器人完成。
//
// 工作方式（状态机）：
//   ExecutorNode 内部维护一个"状态机"（State Machine）。
//   状态机就像流程图：每次处于某个状态，等待条件满足后跳转到下一个状态。
//
//   递水任务的状态流转顺序：
//   IDLE -> ASK_USER_LOCATION -> SEARCH_BOTTLE -> APPROACH_BOTTLE
//        -> PICK_BOTTLE -> NAV_TO_USER_ROOM -> FIND_PERSON_LOCAL
//        -> HAND_OVER -> DONE -> IDLE
//
//   异常时：超过重试次数 -> FAILED -> IDLE（降级：导航到客厅交付点）
//
// 话题（Topics）：
//   - 订阅 /nlu/command_json   [std_msgs/String]     接收 NLU 命令 JSON
//   - 发布 /robot/state        [std_msgs/String]     发布当前状态
//   - 发布 /cmd_vel_raw        [geometry_msgs/Twist] 发布原始速度指令
//
// 服务客户端（Service Clients）：
//   - /perception/detect_bottle  ：请求感知节点检测水瓶
//   - /perception/find_person    ：请求感知节点寻找人
//   - /manipulation/pick_bottle  ：请求机械臂抓取水瓶
//   - /manipulation/hand_over    ：请求机械臂递给用户
//   - /navigate_to_pose          ：Nav2 导航到目标（Action）
// =============================================================================

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "robot_msgs/srv/detect_object.hpp"
#include "robot_msgs/srv/find_person.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"

using namespace std::chrono_literals;

class ExecutorNode : public rclcpp::Node
{
public:
// enum class State：状态机中所有可能的状态
// enum class 比普通 enum 更安全：必须写 State::IDLE 而不能直接写 IDLE
  enum class State
  {
    IDLE,              // 空闲，等待指令
    ASK_USER_LOCATION,  // 询问用户在哪个房间（可触发语音追问）
    SEARCH_BOTTLE,     // 用感知节点搜索水瓶
    APPROACH_BOTTLE,   // 导航到水瓶旁边
    PICK_BOTTLE,       // 让机械臂抓取水瓶
    NAV_TO_USER_ROOM,  // 导航到用户所在房间
    FIND_PERSON_LOCAL,  // 在房间内局部搜索用户
    SEARCH_OWNER_GLOBAL,  // 局部找人失败，全屋搜索
    HAND_OVER,         // 递给用户
    DONE,              // 任务完成
    FAILED             // 任务失败（超过重试次数）
  };

  // 构造函数：初始化所有话题、服务客户端和定时器
  ExecutorNode()
  : Node("executor_node")
  {
    // 订阅 NLU 解析结果。NLU 节点把语音文本转成 JSON 字符串并发布到这里。
    // 例如：{"intent":"deliver_water","slots":{"object":"bottle"}}
    command_sub_ = create_subscription<std_msgs::msg::String>(
      "/nlu/command_json", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        // 判断是否是"递水"指令（简单字符串搜索）
        if (msg->data.find("deliver_water") != std::string::npos) {
          // 收到递水指令：进入"询问用户位置"状态，重置重试计数
          set_state(State::ASK_USER_LOCATION);
          retry_count_ = 0;
        }
      });

    // 创建服务客户端：向其他节点发起"服务请求"
    // 类比打电话：你拨号（发请求），对方接听后给你答复
    detect_client_ = create_client<robot_msgs::srv::DetectObject>("/perception/detect_bottle");
    find_person_client_ = create_client<robot_msgs::srv::FindPerson>("/perception/find_person");
    pick_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/pick_bottle");
    handover_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/hand_over");

    // Nav2 使用 Action（动作）而非普通 Service，因为导航是长时间任务，支持进度反馈
    nav_client_ = rclcpp_action::create_client<nav2_msgs::action::NavigateToPose>(
      this, "/navigate_to_pose");
    // 发布当前状态，供监控界面或其他节点观察
    state_pub_ = create_publisher<std_msgs::msg::String>("/robot/state", 10);
    // 发布原始速度指令，由 robot_safety 节点限速后转发给底盘
    cmd_raw_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel_raw", 10);

    // 每 1 秒调用一次 tick()，推进状态机
    timer_ = create_wall_timer(1s, std::bind(&ExecutorNode::tick, this));
    // 启动时立刻发布初始状态（IDLE）
    publish_state();
  }

private:
  // tick：每秒被定时器调用一次，负责推进状态机
  // 相当于"心跳"——每次都检查：当前状态该做什么？条件满足了吗？
  void tick()
  {
    // 计数器：记录当前状态已经持续了多少个 tick（每 tick 约 1 秒）
    // 只在"正在工作"时计数（空闲/完成/失败时归零）
    if (current_state_ != State::IDLE && current_state_ != State::DONE &&
      current_state_ != State::FAILED)
    {
      ++state_ticks_;
    } else {
      state_ticks_ = 0;
    }

    // 状态机主逻辑：根据当前状态决定下一步
    switch (current_state_) {
      case State::IDLE:
        // 空闲中，什么都不做，等待 /nlu/command_json 触发
        break;
      case State::ASK_USER_LOCATION:
        // 如果用户没有提供位置，这里可以发起语音追问“你在哪个房间？”。
        set_state(State::SEARCH_BOTTLE);
        break;
      case State::SEARCH_BOTTLE:
        // TODO(robot): 调 perception service。当前骨架直接推进流程。
        set_state(State::APPROACH_BOTTLE);
        break;
      case State::APPROACH_BOTTLE:
        // 已知水瓶位置，导航过去（真实实现需等待导航完成）
        set_state(State::PICK_BOTTLE);
        break;
      case State::PICK_BOTTLE:
        // 调用机械臂抓取水瓶（真实实现需等待抓取完成）
        set_state(State::NAV_TO_USER_ROOM);
        break;
      case State::NAV_TO_USER_ROOM:
        // TODO(robot): 使用 Nav2 action client 发送目标点并等待结果。
        set_state(State::FIND_PERSON_LOCAL);
        break;
      case State::FIND_PERSON_LOCAL:
        // 先房间内局部找人。
        set_state(State::HAND_OVER);
        break;
      case State::SEARCH_OWNER_GLOBAL:
        // 局部失败后执行全屋搜索。
        set_state(State::HAND_OVER);
        break;
      case State::HAND_OVER:
        // 找到用户，让机械臂把水递过去
        set_state(State::DONE);
        break;
      case State::DONE:
        RCLCPP_INFO(get_logger(), "deliver_water done");
        // 任务完成，回到空闲状态，等待下一条指令
        set_state(State::IDLE);
        break;
      case State::FAILED:
        // 失败降级：导航到客厅交付点。
        RCLCPP_WARN(get_logger(), "deliver_water failed, fallback to living_room handover spot");
        set_state(State::IDLE);
        break;
    }

    // 重试框架：如果一个阶段卡住超时，则累计重试次数。
    // 例如：导航超时（等了 10 秒还没到），就从搜索水瓶重新开始
    if (state_ticks_ > state_timeout_ticks_) {
      ++retry_count_;
      state_ticks_ = 0;
      set_state(State::SEARCH_BOTTLE);
      RCLCPP_WARN(get_logger(), "state timeout -> retry %d/%d", retry_count_, max_retries_);
    }

    // 重试次数超限：进入失败状态，触发降级处理
    if (retry_count_ > max_retries_) {
      set_state(State::FAILED);
    }

    // 预留联调链路：executor 发布 /cmd_vel_raw，robot_safety 统一限速后输出 /cmd_vel。
    // 当前骨架发布空速度（真实导航时由 Nav2 填充速度）
    cmd_raw_pub_->publish(geometry_msgs::msg::Twist());
  }

  // set_state：切换到新状态，并立即发布新状态
  // 如果和当前状态相同，不做任何操作（避免重复发布）
  void set_state(State next)
  {
    if (current_state_ == next) {
      return;
    }
    current_state_ = next;
    publish_state();
  }

  // publish_state：把当前状态名（字符串）发布到 /robot/state 话题
  void publish_state() const
  {
    std_msgs::msg::String msg;
    msg.data = state_to_string(current_state_);
    state_pub_->publish(msg);
  }

  // state_to_string：把枚举值转换成可读字符串，供发布和日志使用
  static std::string state_to_string(State state)
  {
    switch (state) {
      case State::IDLE:
        return "IDLE";
      case State::ASK_USER_LOCATION:
        return "ASK_USER_LOCATION";
      case State::SEARCH_BOTTLE:
        return "SEARCH_BOTTLE";
      case State::APPROACH_BOTTLE:
        return "APPROACH_BOTTLE";
      case State::PICK_BOTTLE:
        return "PICK_BOTTLE";
      case State::NAV_TO_USER_ROOM:
        return "NAV_TO_USER_ROOM";
      case State::FIND_PERSON_LOCAL:
        return "FIND_PERSON_LOCAL";
      case State::SEARCH_OWNER_GLOBAL:
        return "SEARCH_OWNER_GLOBAL";
      case State::HAND_OVER:
        return "HAND_OVER";
      case State::DONE:
        return "DONE";
      case State::FAILED:
        return "FAILED";
      default:
        return "UNKNOWN";
    }
  }

  // --- 状态机变量 ---
  State current_state_{State::IDLE};   // 当前状态（初始为 IDLE）
  int retry_count_{0};                 // 当前已重试次数
  int max_retries_{3};                 // 最大允许重试次数
  int state_ticks_{0};                 // 当前状态已持续的 tick 数
  int state_timeout_ticks_{10};        // 单个状态最大 tick 数（超过则超时）

  // --- ROS2 通信对象 ---
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_sub_;
  rclcpp::Client<robot_msgs::srv::DetectObject>::SharedPtr detect_client_;
  rclcpp::Client<robot_msgs::srv::FindPerson>::SharedPtr find_person_client_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr pick_client_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr handover_client_;
  rclcpp_action::Client<nav2_msgs::action::NavigateToPose>::SharedPtr nav_client_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_raw_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

// main：程序入口
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExecutorNode>());
  rclcpp::shutdown();
  return 0;
}
