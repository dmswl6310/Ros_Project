#include <ros/ros.h>
#include <knu_ros_lecture/knuRosLecture.h>
#include <geometry_msgs/Twist.h>
#include <boost/thread/mutex.hpp>
#include <stdlib.h>

boost::mutex mutex[2];

float g_distance;

void msgCallback(const knu_ros_lecture::knuRosLecture &msg)
{
	ROS_INFO("received moving data: %.2f", msg.float64Data);

	//mutex[0].lock(); {
       		g_distance = msg.float64Data;
    	//} mutex[0].unlock();

};

geometry_msgs::Twist turtle_move(double dist)
{
	geometry_msgs::Twist moveD;
        ROS_INFO("function in");

	if(dist > -500 && dist <= -400)
	{
		moveD.linear.x = 0.5; moveD.angular.z = 0.25;
	}
	else if(dist > -400 && dist <= -300)
	{
		moveD.linear.x = 0.5; moveD.angular.z = 0.2;
	}
	else if(dist > -300 && dist <= -200)
	{
		moveD.linear.x = 0.5; moveD.angular.z = 0.15;
	}
	else if(dist > -200 && dist <= -100)
	{
		moveD.linear.x = 0.5; moveD.angular.z = 0.1;
	}
	else if(dist > -100 && dist <= 100) //straight direction
	{
		moveD.linear.x = 0.5; moveD.angular.z = 0.0;
	}
	else if(dist > 100 && dist <= 200)
	{
		moveD.linear.x = 0.5; moveD.angular.z = -0.1;
	}
	else if(dist > 200 && dist <= 300)
	{
		moveD.linear.x = 0.5; moveD.angular.z = -0.15;
	}
	else if(dist > 300 && dist <= 400)
	{
		moveD.linear.x = 0.5; moveD.angular.z = -0.2;
	}
	else if(dist > 400 && dist <= 500)
	{
		moveD.linear.x = 0.5; moveD.angular.z = -0.25;
	}
	else //faild to find
	{
		moveD.linear.x = 0.0; moveD.angular.z = 0.0;
	}
	
	return moveD;
}

int main (int argc, char **argv)
{
	//init
	ros::init(argc, argv, "turtle_follow");
	ros::NodeHandle nh1;
	ros::NodeHandle nh2;
	//decleation of subscriber
	ros::Subscriber sub = nh1.subscribe("user_msg_tutorial", 100, &msgCallback);
	
	//create a publisher object
	ros::Publisher pub = nh2.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

	float distance;

	ros::Rate rate(10);
	while(ros::ok()) {
		geometry_msgs::Twist moveData;

		//mutex[1].lock(); {
           		distance = g_distance;
        	//} mutex[1].unlock();
		
                
		moveData = turtle_move(distance);		
                ROS_INFO("to move: %.2f", moveData.angular.z);
		pub.publish(moveData);

 		ros::spinOnce();
	}

		
}
