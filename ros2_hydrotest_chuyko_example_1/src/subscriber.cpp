#include "rclcpp/rclcpp.hpp"

#include "ros2_hydrotest_chuyko_interfaces/msg/example_message.hpp"

class SubscriberNode : public rclcpp::Node {
public:
    SubscriberNode() : Node("subscriber_node") {
        subscriber_ = this->create_subscription<ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage>(
            "counter_topic", 10, std::bind(&SubscriberNode::topic_callback, this, std::placeholders::_1));
    }


private:
    void topic_callback(const ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Received: %ld", msg->counter);
    }

    rclcpp::Subscription<ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage>::SharedPtr subscriber_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}