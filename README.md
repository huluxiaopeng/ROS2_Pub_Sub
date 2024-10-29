# ROS2_Pub_Sub
ros2 listener and talker

# ros2_speed

ros2 speed node

ros创建工作区

ros2 pkg create --build-type ament_cmake ros_speed --dependencies rclcpp std_msgs



编译以及配置

```
colcon build --packages-select ros_speed
```

```
. install/setup.bash
```



执行进程

```
ros2 run ros_speed talker 1  (数据大小 单位k ) 1 （频率 单位hz）
```

```
ros2 run ros_speed listener
```
