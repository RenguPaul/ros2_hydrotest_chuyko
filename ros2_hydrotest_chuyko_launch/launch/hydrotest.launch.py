#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # C++ nodes
        Node(
            package='ros2_hydrotest_chuyko_example_1',
            executable='publisher_node',
            name='cpp_publisher'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_1',
            executable='subscriber_node',
            name='cpp_subscriber'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_1',
            executable='service_server_node',
            name='cpp_service_server'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_1',
            executable='service_client_node',
            name='cpp_service_client'
        ),
        
        # Python nodes
        Node(
            package='ros2_hydrotest_chuyko_example_2',
            executable='publisher_node',
            name='py_publisher'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_2',
            executable='subscriber_node',
            name='py_subscriber'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_2',
            executable='service_server_node',
            name='py_service_server'
        ),
        Node(
            package='ros2_hydrotest_chuyko_example_2',
            executable='service_client_node',
            name='py_service_client'
        ),
    ])