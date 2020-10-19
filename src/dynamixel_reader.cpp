#include "ros/ros.h"
#include "ros/time.h"

#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "sensor_msgs/JointState.h"


std_msgs::String joint1_name, joint2_name;
std_msgs::Float64 joint1_pos, joint2_pos;
std_msgs::Float64 joint1_vel, joint2_vel;
std_msgs::Float64 joint1_eff, joint2_eff;


void monitorJointState_callback(const sensor_msgs::JointState::ConstPtr& jointstate){
  joint1_name.data = jointstate->name[0];
  joint2_name.data = jointstate->name[1];

  joint1_pos.data = jointstate->position[0];    // ポジション読み出し    loop_rate.sleep();
  joint2_pos.data = jointstate->position[1];    // ポジション読み出し

  joint1_vel.data = jointstate->velocity[0];    // 速度読み出し
  joint2_vel.data = jointstate->velocity[1];    // 速度読み出し
 
  joint1_eff.data = jointstate->effort[0];    // 負荷読み出し
  joint2_eff.data = jointstate->effort[1];    // 負荷読み出し
}

int main(int argc, char **argv){
  ros::init(argc, argv, "dynamixel_reader");
  ros::NodeHandle nh;

  ros::Subscriber sub_joints;
  sub_joints = nh.subscribe("/dynamixel_workbench/joint_states", 10, monitorJointState_callback);
  ros::Rate loop_rate(10);  // 制御周期10Hz設定
 
  while (ros::ok()) { // 無限ループ
    ros::spinOnce();   // コールバック関数を呼ぶ
    loop_rate.sleep();  //wait
    ROS_INFO("Joint1(%s)= %f | %f | %f ||| Joint2(%s)= %f | %f | %f ", joint1_name.data.c_str(),joint1_pos.data,joint1_vel.data,joint1_eff.data,joint2_name.data.c_str(),joint2_pos.data,joint2_vel.data,joint2_eff.data);
  }
   
  return 0;
}