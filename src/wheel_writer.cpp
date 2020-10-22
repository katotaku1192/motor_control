#include "ros/ros.h"
#include "ros/time.h"
 
#include "geometry_msgs/Twist.h"

 
int main(int argc, char **argv){
    ros::init(argc, argv, "wheel_writer");  // ノードの初期化
    ros::NodeHandle nh; // ノードハンドラ  
 
    //パブリッシャの作成
    ros::Publisher wheel_pub = nh.advertise<geometry_msgs::Twist>("/dynamixel_workbench/cmd_vel",1);
 
    ros::Rate loop_rate(10);  // 制御周期10Hz
   
    geometry_msgs::Twist vel;

    vel.linear.x = 0.05;
    vel.linear.y = 0.0;
    vel.linear.z = 0.0;

    vel.angular.x = 0.0;
    vel.angular.y = 0.0;
    vel.angular.z = 0.0;
   
    while(ros::ok()) {
        wheel_pub.publish(vel);
        loop_rate.sleep();
        ROS_INFO("linear : %.2f, %.2f, %.2f    angular : %f.2, %.2f, %.2f", vel.linear.x, vel.linear.y, vel.linear.z, vel.angular.x, vel.angular.y, vel.angular.z);
    }
 
    return 0;
}