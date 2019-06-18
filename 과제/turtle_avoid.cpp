#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <boost/thread/mutex.hpp>
#include <tf/tf.h>
#include <math.h>
#include <sensor_msgs/LaserScan.h>
#include <stdlib.h>
#include <time.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variable
nav_msgs::Odometry g_odom;
sensor_msgs::LaserScan g_scan;
boost::mutex mutex[2];
int flag_coll = 1;


template<typename T>
inline bool isnan(T value)
{
    return value != value;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// callback function
void
odomMsgCallback(const nav_msgs::Odometry &msg)
{
    // receive a '/odom' message with the mutex
    mutex[0].lock(); {
        g_odom = msg;
    } mutex[0].unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// callback function
void
scanMsgCallback(const sensor_msgs::LaserScan& msg)
{
    // receive a '/odom' message with the mutex
    mutex[1].lock(); {
        g_scan = msg;
    } mutex[1].unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
void
convertScan2XYZs(sensor_msgs::LaserScan& lrfScan)
{
    int nRangeSize = (int)lrfScan.ranges.size();
    int count = 0;
    float sum = 0;
    float average = 9999;

    for(int i=0; i<nRangeSize; i++) {
        double dRange = lrfScan.ranges[i];
        //0.9 범위 내의 거리의 평균 구하기.
        
        //printf(" 최대 사이즈 %d \n",nRangeSize);
        if( !isnan(dRange) && dRange <= 0.9 ) {
		count++;
		sum += dRange;
        } 
        // 원하는 각도를 넘어서면 , 종료. //70 ~ 290 
	if(i==70)
		i += 220;
	}
    //만나지 않을때. 
    if(count == 0) {
	ROS_INFO("-70~70도 사이의 장애물 정보 없음 \n");
	return;
    } else {
	average = sum/count;
    }
    ROS_INFO("-70~70도 사이의 장애물까지의 평균거리 : %f\n", average);
    //충돌가능성 탐지
    if(average <= 0.30) {
	flag_coll = 0;
	return;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
int main(int argc, char **argv)
{
    int i;
    ros::init(argc, argv, "turtle__avoid");
    // Ros initialization
    ros::NodeHandle nhp, nhs;
    // Decleation of subscriber
    ros::Subscriber subScan = nhs.subscribe("/scan", 10, &scanMsgCallback);
    // Create a publisher object
    ros::Publisher pub = nhp.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
	
    sensor_msgs::LaserScan scan;
    ros::Rate rate(10);
	
    while(ros::ok()) {
	mutex[1].lock(); {
	scan = g_scan;
        } mutex[1].unlock();
	
	convertScan2XYZs(scan);
	if (flag_coll == 0)
	{
	geometry_msgs::Twist moveD;
	moveD.linear.x = -0.05;
	moveD.angular.z = 0;
	pub.publish(moveD);
	flag_coll = 1;
	}
    }
	
    return 0;
}
