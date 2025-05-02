import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/pavel/Desktop/BaumanProjects/ros2_hydrotest_chuyko/install/ros2_hydrotest_chuyko_example_2'
