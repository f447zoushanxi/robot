// Copyright (c) 2026.
//
// SPDX-License-Identifier: Apache-2.0

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
  enum class State
  {
    IDLE,
    ASK_USER_LOCATION,
    SEARCH_BOTTLE,
    APPROACH_BOTTLE,
    PICK_BOTTLE,
    NAV_TO_USER_ROOM,
    FIND_PERSON_LOCAL,
    SEARCH_OWNER_GLOBAL,
    HAND_OVER,
    DONE,
    FAILED
  };

  ExecutorNode()
  : Node("executor_node")
  {
    command_sub_ = create_subscription<std_msgs::msg::String>(
      "/nlu/command_json", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        if (msg->data.find("deliver_water") != std::string::npos) {
          set_state(State::ASK_USER_LOCATION);
          retry_count_ = 0;
        }
      });

    detect_client_ = create_client<robot_msgs::srv::DetectObject>("/perception/detect_bottle");
    find_person_client_ = create_client<robot_msgs::srv::FindPerson>("/perception/find_person");
    pick_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/pick_bottle");
    handover_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/hand_over");

    nav_client_ = rclcpp_action::create_client<nav2_msgs::action::NavigateToPose>(
      this, "/navigate_to_pose");
    state_pub_ = create_publisher<std_msgs::msg::String>("/robot/state", 10);
    cmd_raw_pub_ = create_publisher<geometry_msgs::msg::Twist>("/cmd_vel_raw", 10);

    timer_ = create_wall_timer(1s, std::bind(&ExecutorNode::tick, this));
    publish_state();
  }

private:
  void tick()
  {
    if (current_state_ != State::IDLE && current_state_ != State::DONE &&
      current_state_ != State::FAILED)
    {
      ++state_ticks_;
    } else {
      state_ticks_ = 0;
    }

    switch (current_state_) {
      case State::IDLE:
        break;
      case State::ASK_USER_LOCATION:
        // 如果用户没有提供位置，这里可以发起语音追问“你在哪个房间？”。
        set_state(State::SEARCH_BOTTLE);
        break;
      case State::SEARCH_BOTTLE:
        // TODO: 调 perception service。当前骨架直接推进流程。
        set_state(State::APPROACH_BOTTLE);
        break;
      case State::APPROACH_BOTTLE:
        set_state(State::PICK_BOTTLE);
        break;
      case State::PICK_BOTTLE:
        set_state(State::NAV_TO_USER_ROOM);
        break;
      case State::NAV_TO_USER_ROOM:
        // TODO: 使用 Nav2 action client 发送目标点并等待结果。
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
        set_state(State::DONE);
        break;
      case State::DONE:
        RCLCPP_INFO(get_logger(), "deliver_water done");
        set_state(State::IDLE);
        break;
      case State::FAILED:
        // 失败降级：导航到客厅交付点。
        RCLCPP_WARN(get_logger(), "deliver_water failed, fallback to living_room handover spot");
        set_state(State::IDLE);
        break;
    }

    // 重试框架：如果一个阶段卡住超时，则累计重试次数。
    if (state_ticks_ > state_timeout_ticks_) {
      ++retry_count_;
      state_ticks_ = 0;
      set_state(State::SEARCH_BOTTLE);
      RCLCPP_WARN(get_logger(), "state timeout -> retry %d/%d", retry_count_, max_retries_);
    }

    if (retry_count_ > max_retries_) {
      set_state(State::FAILED);
    }

    // 预留联调链路：executor 发布 /cmd_vel_raw，robot_safety 统一限速后输出 /cmd_vel。
    cmd_raw_pub_->publish(geometry_msgs::msg::Twist());
  }

  void set_state(State next)
  {
    if (current_state_ == next) {
      return;
    }
    current_state_ = next;
    publish_state();
  }

  void publish_state() const
  {
    std_msgs::msg::String msg;
    msg.data = state_to_string(current_state_);
    state_pub_->publish(msg);
  }

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

  State current_state_{State::IDLE};
  int retry_count_{0};
  int max_retries_{3};
  int state_ticks_{0};
  int state_timeout_ticks_{10};

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

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExecutorNode>());
  rclcpp::shutdown();
  return 0;
}
