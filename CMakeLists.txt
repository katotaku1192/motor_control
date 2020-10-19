cmake_minimum_required(VERSION 3.0.2)
project(motor_control)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  trajectory_msgs
)

catkin_package(CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs )

include_directories(${catkin_INCLUDE_DIRS})

add_executable(dynamixel_reader src/dynamixel_reader.cpp)
target_link_libraries(dynamixel_reader ${catkin_LIBRARIES})
