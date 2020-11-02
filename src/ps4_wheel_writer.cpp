#include "ros/ros.h"
#include "ros/time.h"
 
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"



class JoyWheel{
    public:
        ros::NodeHandle nh;
        ros::Subscriber joy_sub;
        ros::Publisher front_twist_pub;
        ros::Publisher back_twist_pub;
    
        JoyWheel();
        void joy_callback(const sensor_msgs::Joy::ConstPtr& msg);
};


JoyWheel::JoyWheel(){
    joy_sub = nh.subscribe("/joy", 1, &JoyWheel::joy_callback, this);
    front_twist_pub = nh.advertise<geometry_msgs::Twist>("/front/dynamixel_workbench/cmd_vel",1);
    back_twist_pub = nh.advertise<geometry_msgs::Twist>("/back/dynamixel_workbench/cmd_vel",1);
}


void JoyWheel::joy_callback(const sensor_msgs::Joy::ConstPtr& msg){
    if(msg->buttons[5] == 1){
        geometry_msgs::Twist twist;

        // max linear speed [m/s]
        double max_linear_speed = 0.2;
        // max angular speed [rad/s]
        double max_angular_speed = 0.50;


        // between wheels [m]
        double between_wheels = 0.326;

        twist.linear.x = -between_wheels / 2 * max_angular_speed * msg->axes[2];
        twist.angular.z = -max_linear_speed * msg->axes[5];

        front_twist_pub.publish(twist);
        back_twist_pub.publish(twist);
    }

    else{
        geometry_msgs::Twist twist;

        twist.linear.x = 0.0;
        twist.angular.z = 0.0;

        front_twist_pub.publish(twist);
        back_twist_pub.publish(twist);
    }
}



int main(int argc, char** argv) {
    ros::init(argc, argv, "ps4_wheel_writer");

    JoyWheel joy_wheel;

    ros::Rate loop_rate(10);
	while(ros::ok()){
		ros::spinOnce();
		loop_rate.sleep();
	}
    return 0;
}