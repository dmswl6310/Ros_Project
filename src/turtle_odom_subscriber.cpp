#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <boost/thread/mutex.hpp>
#include <tf/tf.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variable
boost::mutex mutex;
nav_msgs::Odometry g_odom;

void odomMsgCallback(const nav_msgs::Odometry &odom)
{
    ROS_INFO("[pose.pose.position.x] : %f\n", odom.pose.pose.position.x);
    ROS_INFO("[pose.pose.position.y] : %f\n", odom.pose.pose.position.y);
    ROS_INFO("[pose.pose.position.z] : %f\n", odom.pose.pose.position.z);

    ROS_INFO("[pose.pose.orientation.x] : %f\n", odom.pose.pose.orientation.x);
    ROS_INFO("[pose.pose.orientation.y] : %f\n", odom.pose.pose.orientation.y);
    ROS_INFO("[pose.pose.orientation.z] : %f\n", odom.pose.pose.orientation.z);
    ROS_INFO("[pose.pose.orientation.w] : %f\n", odom.pose.pose.orientation.w);
}

int main(int argc, char **argv)
{
    // ROS 초기화
    ros::init(argc, argv, "turtle_position_move");
    ros::NodeHandle nhp, nhs;
    ros::Subscriber sub = nhs.subscribe("/odom", 100, &odomMsgCallback);

    ros::spin();
    return 0;
}

