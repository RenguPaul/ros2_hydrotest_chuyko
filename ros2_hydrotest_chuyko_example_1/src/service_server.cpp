#include "rclcpp/rclcpp.hpp"
#include "ros2_hydrotest_chuyko_interfaces/srv/example_service.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class ServiceServerNode : public rclcpp::Node {
public:
    ServiceServerNode() : Node("service_server_node") {
        service_ = this->create_service<ros2_hydrotest_chuyko_interfaces::srv::ExampleService>(
            "string_length_service",
            std::bind(&ServiceServerNode::calculate_length, this, _1, _2));
    }



    
private:
    void calculate_length(
        const ros2_hydrotest_chuyko_interfaces::srv::ExampleService::Request::SharedPtr request,
        ros2_hydrotest_chuyko_interfaces::srv::ExampleService::Response::SharedPtr response) {
        
        response->length = request->input_string.length();
        RCLCPP_INFO(this->get_logger(), "Received: '%s', returning: %ld", 
                   request->input_string.c_str(), response->length);
    }

    rclcpp::Service<ros2_hydrotest_chuyko_interfaces::srv::ExampleService>::SharedPtr service_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServiceServerNode>());
    rclcpp::shutdown();
    return 0;
}