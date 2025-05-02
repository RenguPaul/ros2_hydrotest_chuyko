#include "rclcpp/rclcpp.hpp"
#include "ros2_hydrotest_chuyko_interfaces/srv/example_service.hpp"
#include <chrono>
#include <memory>
#include <vector>

using namespace std::chrono_literals;

class ServiceClientNode : public rclcpp::Node {
public:
    ServiceClientNode() : Node("service_client_node"), count_(0) {
        client_ = this->create_client<ros2_hydrotest_chuyko_interfaces::srv::ExampleService>("string_length_service");
        timer_ = this->create_wall_timer(2s, std::bind(&ServiceClientNode::send_request, this));
    }

private:
    void send_request() {
        if (!client_->wait_for_service(1s)) {
            RCLCPP_WARN(this->get_logger(), "Service not available, waiting...");
            return;
        }

        auto request = std::make_shared<ros2_hydrotest_chuyko_interfaces::srv::ExampleService::Request>();
        request->input_string = "Test string #" + std::to_string(++count_);

        auto result_future = client_->async_send_request(request);
        std::future_status status = result_future.wait_for(1s);
        
        if (status == std::future_status::ready) {
            auto response = result_future.get();
            RCLCPP_INFO(this->get_logger(), "String: '%s', Length: %ld", 
                       request->input_string.c_str(), response->length);
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service");
        }
    }

    rclcpp::Client<ros2_hydrotest_chuyko_interfaces::srv::ExampleService>::SharedPtr client_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServiceClientNode>());
    rclcpp::shutdown();
    return 0;
}