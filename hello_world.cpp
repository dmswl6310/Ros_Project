#include <ros/ros.h>
#include <sstream>

int main(int argc,char **argv){

	ros::init(argc,argv,"hello_world_node");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);

	int count = 1;

	while(ros::ok()){
		std::stringstream ss;
		ss << "hello world : " << count ;
		ROS_INFO("%s",ss.str().c_str());
		loop_rate.sleep();
		count++;
	}

	return 0;
}
