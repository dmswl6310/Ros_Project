#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "turtlesim_random_move");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    srand(time(0));

    ros::Rate rate(200000);
  
    while(ros::ok()) {
        geometry_msgs::Twist msg;
        msg.linear.x = double(rand()) / double(RAND_MAX);
        msg.angular.z = 2.0 * double(rand()) / double(RAND_MAX) - 1.0;
        pub.publish(msg);
        ROS_INFO_STREAM("sending random velocity command :" << " linear=" << msg.linear.x << " angular=" << msg.angular.z);
        rate.sleep();
    }
    return 0;

}