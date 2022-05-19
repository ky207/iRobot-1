# ROS-melodic-simulation-robot-1
Robot simulation with ROS-Melodic gmapping and navigation

Robot simulation：
#1. iRobot-1文件夹作为工作空间。
"""
cd iRobot-1
catkin_make
"""

#2: mapping
##1：在工作空间下，启动terminal终端：
"""
source ./devel/setup.bash
roslaunch simbot mapping.launch
"""

##2：启动仿真环境后，新启动terminal：
"""
source ./devel/setup.bash
rosrun teleop_twist_keyboard teleop_twist_keyboard
"""
确保teleop_twist_keyboard命令窗在激活状态下，通过按键可以控制小车运动，遍历地图，利用激光雷达的点云转换成/scan，gmapping进行建图。

##3：遍历地图后，不要关闭rviz。在map文件夹里，新启动terminal,保存新的地图到map文件夹里：
"""
rosrun map_server map_saver
"""
如果需要更换地图，需要在launch文件里修改导入更换的地图名。


#3:Navigation:
##1： 启动导航
"""
source ./devel/setup.bash
roslaunch simbot navigation.launch
"""
##2：启动后，在rviz里先设置2D pose estimate进行定位，点击小车位置，然后拉住旋转，会出现一个绿色的箭头，让绿色箭头方向与机器人的前进方向一致，即与X轴方向（红色坐标轴）一致。然后设置目标点，2D Nav Goal，同样拉动紫色箭头,设置目标位置机器人的方向。
##3： 机器人Dijkstra算法自动规划路径，然后驱动沿路线行走。个别位置可能过不去，需要调整目标位置，让小车摆脱困境。
##4： gazebo里，小车也按相同路线行走。

可以利用rosbag进行录包，将pointcloud,image数据录制起来，方便后续进行建图研究。
