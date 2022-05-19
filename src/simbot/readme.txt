download VLP16 MODEL:
git clone https://bitbucket.org/DataspeedInc/velodyne_simulator.git

change simbot urdf:

cmd:
source ./devel/setup.bash

roslaunch simbot robot.launch          # rviz for sensor; lidar and camera

roslaunch simbot run.launch              # for gazebo simluation with world map and robot

rosrun teleop_twist_keyboard teleop_twist_keyboard.py               # for keypad controll

rosbag record -a                # record the data with ctrl+c stop

mapping:
roslaunch lego_loam run.launch
rosbag play test.bag --clock -r5
