#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/thread/mutex.hpp>
#include <tf/tf.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variable
boost::mutex mutex;
nav_msgs::Odometry g_odom;

int flag_coll = 1;
void odomMsgCallback(const sensor_msgs::LaserScan &scan)
{
    ROS_INFO("[pose.pose.position.x] : %f\n", scan.angle_min);
    ROS_INFO("[pose.pose.position.y] : %f\n", scan.angle_max);
    ROS_INFO("[pose.pose.position.z] : %f\n", scan.angle_increment);

    int nRangeSize = (int)scan.ranges.size();
    int count = 0;
    float sum = 0;
    float average = 9999;

    for(int i=0; i<nRangeSize; i++) {
        double dRange = scan.ranges[i];
        //0.9 범위 내의 거리의 평균 구하기.
       
        //printf(" 최대 사이즈 %d \n",nRangeSize);
        if( !isnan(dRange) && dRange <= 0.9 ) {
		count++;
		sum += dRange;
        } 
        // 원하는 각도를 넘어서면 , 종료. //70 ~ 290 
	if(i==30)
		i += 360;
	
	}
    //만나지 않을때. 
    if(count == 0) {
	printf("-70~70도 사이의 장애물 정보 없음 \n");
	return;
    } else {
	average = sum/count;
    }
    printf("-70~70도 사이의 장애물까지의 평균거리 : %f\n", average);
    //충돌가능성 탐지
    if(average <= 0.20 && average >= 0.15) {
	flag_coll = 0;
    printf("충돌 가능성 들어감\n");
    }
    /*if(flag_coll == 0){
	
        geometry_msgs::Twist moveD;
	moveD.linear.x = -0.05;
	moveD.angular.z = 0;
	pub.publish(moveD);
	flag_coll = 1;
	}
*/

	}


int main(int argc, char **argv)
{
    // ROS 초기화
    ros::init(argc, argv, "turtle_scan_sub");
    ros::NodeHandle nhp, nhs;
    ros::Subscriber sub = nhs.subscribe("/scan", 100, &odomMsgCallback);

    ros::NodeHandle nh3;
    ros::Publisher pub = nh3.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ros::Rate loopRate(2);
while(ros::ok()) {
ros::spinOnce();
geometry_msgs::Twist moveData;
moveData.linear.x = -0.05;
moveData.angular.z = 0;
pub.publish(moveData);
loopRate.sleep();

}
    ros::spin();
return 0;
}

