#include <ros/ros.h>
#include <knu_ros_lecture/knuRosLecture.h>
#include <string>

int main(int argc, char** argv) {
    ros::init(argc, argv, "user_msg_publisher_tutorial");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<knu_ros_lecture::knuRosLecture>("user_msg_tutorial", 100);
    ros::Rate rate(10);
    int count = 0;

    while(ros::ok()) {
        knu_ros_lecture::knuRosLecture msg;
        msg.int32Data = count;
        msg.float32Data = float(count+1);
        msg.float64Data = double(count+2);
        msg.stringData = "crvl";
        pub.publish(msg);

        ROS_INFO("send msg = %d / %.2f / %2.lf / %s", msg.int32Data, msg.float32Data, msg.float64Data, msg.stringData);
        rate.sleep();
        count+=10;
    }
    return 0;
}