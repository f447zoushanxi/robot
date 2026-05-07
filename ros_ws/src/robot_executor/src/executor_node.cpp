#include <chrono>
#include <functional>
#include <memory>
#include <string>

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

  ExecutorNode() : Node("executor_node")
  {
    command_sub_ = create_subscription<std_msgs::msg::String>(
      "/nlu/command_json", 10,
      [this](const std_msgs::msg::String::SharedPtr msg) {
        if (msg->data.find("deliver_water") != std::string::npos) {
          current_state_ = State::ASK_USER_LOCATION;
          retry_count_ = 0;
        }
      });

    detect_client_ = create_client<robot_msgs::srv::DetectObject>("/perception/detect_bottle");
    find_person_client_ = create_client<robot_msgs::srv::FindPerson>("/perception/find_person");
    pick_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/pick_bottle");
    handover_client_ = create_client<std_srvs::srv::Trigger>("/manipulation/hand_over");

    nav_client_ = rclcpp_action::create_client<nav2_msgs::action::NavigateToPose>(
      this, "/navigate_to_pose");

    timer_ = create_wall_timer(1s, std::bind(&ExecutorNode::tick, this));
  }

private:
  void tick()
  {
    switch (current_state_) {
      case State::IDLE:
        break;
      case State::ASK_USER_LOCATION:
        // 如果用户没有提供位置，这里可以发起语音追问“你在哪个房间？”。
        current_state_ = State::SEARCH_BOTTLE;
        break;
      case State::SEARCH_BOTTLE:
        // TODO: 调 perception service。当前骨架直接推进流程。
        current_state_ = State::APPROACH_BOTTLE;
        break;
      case State::APPROACH_BOTTLE:
        current_state_ = State::PICK_BOTTLE;
        break;
      case State::PICK_BOTTLE:
        current_state_ = State::NAV_TO_USER_ROOM;
        break;
      case State::NAV_TO_USER_ROOM:
        // TODO: 使用 Nav2 action client 发送目标点并等待结果。
        current_state_ = State::FIND_PERSON_LOCAL;
        break;
      case State::FIND_PERSON_LOCAL:
        // 先房间内局部找人。
        current_state_ = State::HAND_OVER;
        break;
      case State::SEARCH_OWNER_GLOBAL:
        // 局部失败后执行全屋搜索。
        current_state_ = State::HAND_OVER;
        break;
      case State::HAND_OVER:
        current_state_ = State::DONE;
        break;
      case State::DONE:
        RCLCPP_INFO(get_logger(), "deliver_water done");
        current_state_ = State::IDLE;
        break;
      case State::FAILED:
        // 失败降级：导航到客厅交付点。
        RCLCPP_WARN(get_logger(), "deliver_water failed, fallback to living_room handover spot");
        current_state_ = State::IDLE;
        break;
    }

    // 重试框架占位：超时或失败时增加 retry_count_，超过阈值转 FAILED。
    if (retry_count_ > max_retries_) {
      current_state_ = State::FAILED;
    }
  }

  State current_state_{State::IDLE};
  int retry_count_{0};
  int max_retries_{3};

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_sub_;
  rclcpp::Client<robot_msgs::srv::DetectObject>::SharedPtr detect_client_;
  rclcpp::Client<robot_msgs::srv::FindPerson>::SharedPtr find_person_client_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr pick_client_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr handover_client_;
  rclcpp_action::Client<nav2_msgs::action::NavigateToPose>::SharedPtr nav_client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExecutorNode>());
  rclcpp::shutdown();
  return 0;
}
