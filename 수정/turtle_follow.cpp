#include <ros/ros.h>
#include <knu_ros_lecture/knuRosLecture.h>
#include <geometry_msgs/Twist.h>
#include <boost/thread/mutex.hpp>
#include <stdlib.h>
#include <cv_bridge/cv_bridge.h>

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
	srand(time(0));

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
	else // if dist > 500 or dist < -500 than random move 
	{
		moveD.linear.x = 0.5; moveD.angular.z = 2.*double(rand()) / double(RAND_MAX) - 1.;
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
	ros::Subscriber sub = nh1.subscribe("turtle_follow", 100, &msgCallback);
	
	//create a publisher object
	ros::Publisher pub = nh2.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

	float distance;

	ros::Rate loopRate(2);

	while(ros::ok()) {
		ros::spinOnce();
		geometry_msgs::Twist moveData;

		//mutex[1].lock(); {
           		distance = g_distance;
        	//} mutex[1].unlock();
		
                
		moveData = turtle_move(distance);		
                ROS_INFO("line.x: %.2f, angular.z: %.2f", moveData.linear.x, moveData.angular.z);
		pub.publish(moveData);

                //moveData.linear.x = 0;
                //moveData.angular.z = 0;
                //pub.publish(moveData);
                
		loopRate.sleep();
	}

		
}
