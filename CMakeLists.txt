cmake_minimum_required(VERSION 3.0.2)
project(motor_control)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  trajectory_msgs
  geometry_msgs
)

catkin_package(CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs trajectory_msgs geometry_msgs)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(dynamixel_reader src/dynamixel_reader.cpp)
target_link_libraries(dynamixel_reader ${catkin_LIBRARIES})

add_executable(dynamixel_writer src/dynamixel_writer.cpp)
target_link_libraries(dynamixel_writer ${catkin_LIBRARIES})

add_executable(wheel_writer src/wheel_writer.cpp)
target_link_libraries(wheel_writer ${catkin_LIBRARIES})

add_executable(ps4_wheel_writer src/ps4_wheel_writer.cpp)
target_link_libraries(ps4_wheel_writer ${catkin_LIBRARIES})
