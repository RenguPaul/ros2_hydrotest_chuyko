#include "rclcpp/rclcpp.hpp"
#include "ros2_hydrotest_chuyko_interfaces/msg/example_message.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node {
public:
    PublisherNode() : Node("publisher_node"), count_(0) {
        publisher_ = this->create_publisher<ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage>("counter_topic", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&PublisherNode::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage();
        message.counter = ++count_;
        RCLCPP_INFO(this->get_logger(), "Publishing: %ld", message.counter);
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ros2_hydrotest_chuyko_interfaces::msg::ExampleMessage>::SharedPtr publisher_;
    int64_t count_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}